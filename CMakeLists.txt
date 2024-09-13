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

# Для выполнения тестов
add_executable(UserTests tests/UserTests.cpp src/User.cpp src/UserRepository.cpp)
target_link_libraries(UserTests gtest gtest_main pthread ${MYSQL_LIB} OpenSSL::SSL)

