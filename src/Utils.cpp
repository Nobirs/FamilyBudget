#include "Utils.h"
#include <sstream>
#include <iomanip>

// Реализация утилитарной функции для форматирования даты
std::string formatDate(time_t rawTime) {
    struct tm *timeInfo = localtime(&rawTime);  // Преобразуем time_t в структуру tm

    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%Y-%m-%d %H:%M:%S");  // Форматирование даты как YYYY-MM-DD HH:MM:SS

    return oss.str();  // Возвращаем строку
}
