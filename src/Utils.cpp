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

time_t stringToTimeT(const std::string& dateTimeStr) {
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    // Парсим строку в структуру tm
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        throw std::runtime_error("Невозможно распарсить строку даты и времени");
    }
    // Преобразуем tm в time_t
    return std::mktime(&tm);
}