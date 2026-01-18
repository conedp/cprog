#include "film.h"
#include <string.h>


/*
Функция считывает из файла информация об одном фильме: название, имя режиссёра и год выхода.
Каждое поле считывается с новой строки.
Принимает на вход файловую переменную и указатель на структуру "фильм"
*/
int film_read(FILE *f, struct film_t *pfilm)
{
    char title_buf[IN_TITLE_LEN];
    size_t title_len;
    char name_buf[IN_NAME_LEN + 2];
    size_t name_len;
    int year;

    // Ввод названия фильма
    if (!fgets(title_buf, sizeof(title_buf), f))
        return ERR_IO;
    title_len = strlen(title_buf);
    if (title_len != 0 && title_buf[title_len - 1] == '\n')
    {
        title_buf[title_len - 1] = 0;
        title_len -= 1;
    }
    // Проверка на пустую строку и слишком длинную строку
    if (title_len == 0)
        return ERR_RANGE;
    if (title_len > TITLE_LEN)
        return ERR_BUF_TOO_SMALL;

    // Ввод имени режиссёра
    if (!fgets(name_buf, sizeof(name_buf), f))
        return ERR_IO;
    name_len = strlen(name_buf);
    if (name_len != 0 && name_buf[name_len - 1] == '\n')
    {
        name_buf[name_len - 1] = 0;
        name_len -= 1;
    }
    // Проверка на пустую строку и слишком длинную строку
    if (name_len == 0)
        return ERR_RANGE;
    if (name_len > NAME_LEN)
        return ERR_BUF_TOO_SMALL;

    // Ввод года выхода (возможна оошибка при вводе из stdin)
    if (fscanf(f, "%d\n", &year) != 1)
        return ERR_IO;
    if (year <= 0)
        return ERR_RANGE;

    // Перенос данных в структуру
    strcpy(pfilm->title, title_buf);
    strcpy(pfilm->name, name_buf);
    pfilm->year = year;
    return OK;
}


/*
Функция печатает информацию об одном фильме в файл (поток). Каждое поле с новой строки.
Принимает на вход файловую переменную и структуру с данными о фильме (по указателю)
*/
int film_print(FILE *f, const struct film_t *pfilm)
{
    if (fprintf(f, "%s\n", pfilm->title) < 0)
        return ERR_FILE_WRITE;
    if (fprintf(f, "%s\n", pfilm->name) < 0)
        return ERR_FILE_WRITE;
    if (fprintf(f, "%d\n", pfilm->year) < 0)
        return ERR_FILE_WRITE;
    return OK;
}


/*
Функция сравнивает фильмы по названию. Возвращает число > 0 если l > r, число < 0 если l < r и 0, если l == r.
Принимает на вход структуры сравниваемых фильмов (через указатели)
*/
int film_cmp_by_title(const struct film_t *l, const struct film_t *r)
{
    return strcmp(l->title, r->title);
}


/*
Функция сравнивает фильмы по имени режиссёра. Возвращает число > 0 если l > r, число < 0 если l < r и 0, если l == r.
Принимает на вход структуры сравниваемых фильмов (через указатели)
*/
int film_cmp_by_name(const struct film_t *l, const struct film_t *r)
{
    return strcmp(l->name, r->name);
}


/*
Функция сравнивает фильмы по году. Возвращает число > 0 если l > r, число < 0 если l < r и 0, если l == r.
Принимает на вход структуры сравниваемых фильмов (через указатели)
*/
int film_cmp_by_year(const struct film_t *l, const struct film_t *r)
{
    return l->year - r->year;
}
