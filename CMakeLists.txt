cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FamilyBudget)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Добавить директории с исходным кодом
add_executable(FamilyBudget main.cpp)

# Добавить поддержку Qt, если собираете оконную версию
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(FamilyBudget Qt5::Widgets)

# Добавить поддержку MySQL
find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
target_link_libraries(FamilyBudget ${MYSQL_LIBRARIES})
