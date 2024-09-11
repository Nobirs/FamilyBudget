cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FamilyBudget)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Добавить директории с исходным кодом
add_executable(FamilyBudget main.cpp)


# Добавить поддержку MySQL

# Найти библиотеку MySQL
find_library(MYSQL_LIB mysqlclient HINTS /usr/lib /usr/lib/x86_64-linux-gnu /lib/x86_64-linux-gnu/)

# Подключение заголовочных файлов MySQL
include_directories(/usr/include/mysql /lib/x86_64-linux-gnu/)

target_link_libraries(FamilyBudget ${MYSQL_LIB})



# set(CMAKE_PREFIX_PATH "/lib/x86_64-linux-gnu/")
# include_directories(/usr/include/mysql)

# Найдите MySQL библиотеки вручную
# find_library(MYSQL_LIB NAMES mysqlclient PATHS /lib/x86_64-linux-gnu/)
# target_link_libraries(FamilyBudget ${MYSQL_LIB})

# Добавить поддержку Qt, если собираете оконную версию
# find_package(Qt5 COMPONENTS Widgets REQUIRED)
# target_link_libraries(FamilyBudget Qt5::Widgets)