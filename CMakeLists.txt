cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FamilyBudget)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Укажи путь к Qt
set(CMAKE_PREFIX_PATH "/opt/Qt/lib/cmake")

# Найди необходимые модули Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Автоматическая генерация MOC, UIC, RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Добавить исполняемый файл для основного приложения
add_executable(FamilyBudget main.cpp)

# Подключи необходимые библиотеки Qt
target_link_libraries(FamilyBudget PRIVATE Qt6::Widgets)

# Подключение заголовочных файлов MySQL
include_directories(/usr/include/mysql /lib/x86_64-linux-gnu/)
# Найти библиотеку MySQL
find_library(MYSQL_LIB mysqlclient HINTS /usr/lib /usr/lib/x86_64-linux-gnu /lib/x86_64-linux-gnu/)

# Подключение библиотеки OpenSSL
find_package(OpenSSL REQUIRED)
# Линковка основного приложения с MySQL и OpenSSL
target_link_libraries(FamilyBudget PRIVATE ${MYSQL_LIB} OpenSSL::SSL)

# Добавляем Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Используем GLOB для поиска всех тестовых файлов
file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
file(GLOB SRC_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

## Для выполнения тестов
add_executable(UserTests tests/UserTests.cpp ${SRC_SOURCES})
add_executable(UserRepositoryTests tests/UserRepositoryTests.cpp ${SRC_SOURCES})
add_executable(TransactionTests tests/TransactionTests.cpp ${SRC_SOURCES})
add_executable(TransactionRepositoryTests tests/TransactionRepositoryTests.cpp ${SRC_SOURCES})
add_executable(CategoryTests tests/CategoryTests.cpp ${SRC_SOURCES})
add_executable(BudgetTests tests/BudgetTests.cpp ${SRC_SOURCES})
add_executable(AllTests ${TEST_SOURCES} ${SRC_SOURCES})

# Линкуем с Google Test и pthread
target_link_libraries(UserTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(TransactionTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(BudgetTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(TransactionRepositoryTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(UserRepositoryTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(CategoryTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)
target_link_libraries(AllTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)

enable_testing()
add_test(UserTests UserTests)
add_test(TransactionTests TransactionTests)
add_test(BudgetTests BudgetTests)
add_test(TransactionRepositoryTests TransactionRepositoryTests)
add_test(UserRepositoryTests UserRepositoryTests)
add_test(CategoryTests CategoryTests)