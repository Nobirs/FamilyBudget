cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FamilyBudget)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Добавить директории с исходным кодом
add_executable(FamilyBudget main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Найти библиотеку MySQL
find_library(MYSQL_LIB mysqlclient HINTS /usr/lib /usr/lib/x86_64-linux-gnu /lib/x86_64-linux-gnu/)

# Подключение заголовочных файлов MySQL
include_directories(/usr/include/mysql /lib/x86_64-linux-gnu/)

# Подключение библиотеки OpenSSL
find_package(OpenSSL REQUIRED)

# Линковка основного приложения
target_link_libraries(FamilyBudget ${MYSQL_LIB} OpenSSL::SSL)

# Добавляем Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# Указываем директории с исходниками
include_directories(${CMAKE_SOURCE_DIR}/src)


# Используем GLOB для поиска всех тестовых файлов
file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
file(GLOB SRC_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Создаем исполняемый файл для всех тестов

# Для выполнения тестов
add_executable(UserTests tests/UserTests.cpp src/User.cpp)
add_executable(UserRepositoryTests tests/UserRepositoryTests.cpp src/UserRepository.cpp src/User.cpp)
add_executable(TransactionTests tests/TransactionTests.cpp ${SRC_SOURCES})
add_executable(TransactionRepositoryTests tests/TransactionRepositoryTests.cpp ${SRC_SOURCES})
add_executable(CategoryTests tests/CategoryTests.cpp src/CategoryRepository.cpp src/UserRepository.cpp src/Category.cpp src/User.cpp)
add_executable(AllTests ${TEST_SOURCES} ${SRC_SOURCES})

# Линкуем с Google Test и pthread
target_link_libraries(UserTests gtest gtest_main pthread OpenSSL::SSL)
target_link_libraries(TransactionTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(TransactionRepositoryTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(UserRepositoryTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(CategoryTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(AllTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
