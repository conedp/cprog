#include "get_answer.h"
#include <string.h>
#include <ctype.h>
#include "constants.h"
#include "errors.h"


/*
Функция проверяет корректность записи номера телефона в строке.
Принимает на вход char* строку
*/
bool is_a_phone_number(const char *str)
{
    const char *pcur = str;
    // Проверка на ненулевой указатель
    if (!str)
        return false;
    // Пропуск пробельных символов в начале
    while (isspace(*pcur))
        pcur += 1;
    // Проверка на плюс в начале. Если есть плюс, то должен быть и код региона
    if (*pcur == '+')
    {
        pcur += 1;
        if (!isdigit(*pcur))
            return false;
        pcur += 1;
        // Пропуск остальных цифр кода региона
        while (isdigit(*pcur))
            pcur += 1;
    }
    // Проверка на открывающуюся скобочку
    if (*pcur != '(')
        return false;
    pcur += 1;
    // Проверка на корректность кода оператора
    for (size_t i = 0; i < 3; i++)
    {
        if (!isdigit(*pcur))
            return false;
        pcur += 1;
    }
    // Проверка на закрывающуюся скобочку
    if (*pcur != ')')
        return false;
    pcur += 1;
    // Проверка на дефис
    if (*pcur != '-')
        return false;
    pcur += 1;
    // Проверка на корректность первых трёх цифр номера
    for (size_t i = 0; i < 3; i++)
    {
        if (!isdigit(*pcur))
            return false;
        pcur += 1;
    }
    // Проверка на дефис
    if (*pcur != '-')
        return false;
    pcur += 1;
    // Проверка на корректность вторых двух цифр номера
    for (size_t i = 0; i < 2; i++)
    {
        if (!isdigit(*pcur))
            return false;
        pcur += 1;
    }
    // Проверка на дефис
    if (*pcur != '-')
        return false;
    pcur += 1;
    // Проверка на корректность последних двух цифр номера
    for (size_t i = 0; i < 2; i++)
    {
        if (!isdigit(*pcur))
            return false;
        pcur += 1;
    }
    // Пропуск пробельных символов
    while (isspace(*pcur))
        pcur += 1;
    // Проверка на конец строки
    if (*pcur != 0)
        return false;
    pcur += 1;
    
    return true;
}
