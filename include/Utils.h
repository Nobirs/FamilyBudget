#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>

// Декларации утилитарных функций


// функция для форматирования даты в строку
std::string formatDate(time_t rawTime);

// функция для получения даты из форматированной строки
time_t stringToTimeT(const std::string& dateTimeStr);
#endif // UTILS_H
