#include "testing.h"
#include <stdio.h>
#include <string.h>
#include "my_string.h"

int test_strpbrk(void)
{
    unsigned failed_counter = 0;
    char *s1, *s2;
    // puts("my_strpbrk testing");
    // тест 1. Один символ в строке и тот же символ для поиска
    s1 = "a";
    s2 = "a";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 1 failed");
    }
    // тест 2. Строка из разных символов длиной 2, один символ для поиска (искомый на первом месте)
    s1 = "ab";
    s2 = "a";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 2 failed");
    }
    // тест 3. Строка из разных символов длиной 2, один символ для поиска (искомый на втором месте)
    s1 = "ab";
    s2 = "b";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 3 failed");
    }
    // тест 4. Строка длиной больше 2, один символ для поиска (встречается в строке 1 раз)
    s1 = "abrakadabra";
    s2 = "k";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 4 failed");
    }
    // тест 5. Строка длиной больше 2, один символ для поиска (встречается в строке несколько раз)
    s1 = "abrakadabra";
    s2 = "b";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 5 failed");
    }
    // тест 6. Строка длиной больше 2, несколько символов для поиска
    s1 = "abrakadabra";
    s2 = "rkd";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 6 failed");
    }
    // тест 7. Строка из одного символа, несколько символов для поиска (среди которых есть тот, что в строке)
    s1 = "c";
    s2 = "abcd";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 7 failed");
    }
    
    // тест 8. Строка из одного символа, один символ для поиска (отличный от того, что в строке)
    s1 = "a";
    s2 = "b";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 8 failed");
    }
    // тест 9. Ноль символов для поиска
    s1 = "a";
    s2 = "";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 9 failed");
    }
    // тест 10. Пустая строка
    s1 = "";
    s2 = "b";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        //puts("test 10 failed");
    }
    // тест 11. Пустая строка и ноль символов для поиска
    s1 = "";
    s2 = "";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 11 failed");
    }
    // тест 12. Строка длиной больше 1, один символ для поиска (отсутствует в строке)
    s1 = "sad";
    s2 = "k";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 12 failed");
    }
    // тест 13. Строка длиной болььше 1, несколько символов для поиска (все отстутствуют в строке)
    s1 = "sad";
    s2 = "kbc";
    if (strpbrk(s1, s2) != my_strpbrk(s1, s2))
    {
        failed_counter += 1;
        // puts("test 13 failed");
    }
    
    return failed_counter;
}


int test_strspn(void)
{
    unsigned failed_counter = 0;
    char *s1, *s2;
    // puts("my_strspn testing");
    // Строка 1 - строка, в которой ищется максимальное количество символов из Строки 2, расположенных непрерывно начиная с первого
    // тест 1. По одному символу в строках, символ одоин и тот же
    s1 = "a";
    s2 = "a";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 1 failed");
    }
    // тест 2. Строка 1 состоит из двух разных символов, строка 2 - первый символ строки 1
    s1 = "ab";
    s2 = "a";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 2 failed");
    }
    // тест 3. Строка 1 состоит из двух разных символов, строка 2 - второй символ строки 1
    s1 = "ab";
    s2 = "b";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 3 failed");
    }
    // тест 4. Несколько начальных одинаковых символов в строке 1, тот же символ в строке 2
    s1 = "aab";
    s2 = "a";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 4 failed");
    }
    // тест 5. Несколько не начальных одинаковых символов в строке 1, тот же символ в строке 2
    s1 = "abb";
    s2 = "b";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 5 failed");
    }
    // тест 6. Две подстроки из символа из строки 2 в строке 1, более длинный находится в начале
    s1 = "aabba";
    s2 = "a";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 6 failed");
    }
    // тест 7. Две подстроки из символа из строки 2 в строке 1, более длинный находится в конце
    s1 = "abaaa";
    s2 = "a";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 7 failed");
    }
    // тест 8. В строке 2 несколько символов, строка 1 начинается с подстроки из этих символов
    s1 = "bbbaqf";
    s2 = "bcd";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 8 failed");
    }
    // тест 9. В строке 2 несколько символов, строка 1 начинается с символа, не входящего в строку 2
    s1 = "abbdcq";
    s2 = "bcd";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 9 failed");
    }
    // тест 10. В строке 1 две подстроки из символов из строки 2, при этом начальная короче
    s1 = "ccfabdd";
    s2 = "bcd";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 10 failed");
    }
    // тест 11. В строках по одному символу, символы различны
    s1 = "a";
    s2 = "b";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 11 failed");
    }
    // тест 12. Строка 2 пуста
    s1 = "a";
    s2 = "";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 12 failed");
    }
    // тест 13. Строка 1 пуста
    s1 = "";
    s2 = "b";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 13 failed");
    }
    // тест 14. Обе строки пусты
    s1 = "";
    s2 = "";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 14 failed");
    }
    // тест 15. Обе строки из нескольких символов, в строке 1 нет символов из строки 2
    s1 = "abc";
    s2 = "def";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 15 failed");
    }
    
    return failed_counter;
}


int test_strcspn(void)
{
    unsigned failed_counter = 0;
    char *s1, *s2;
    // Строка 1 - строка, в которой ищется максимальное количество символов НЕ из Строки 2, расположенных непрерывно начиная с первого
    // puts("my_strcspn testing");
    // тест 1. Строки длиной 1, символы в них различны
    s1 = "a";
    s2 = "b";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 1 failed");
    }
    // тест 2. Строка 1 длиной 2, в начале символ не из строки 2. Строка 2 длиной 1
    s1 = "ab";
    s2 = "b";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 2 failed");
    }
    // тест 3. Строка 1 длиной 2, в начале символ из строки 2. Строка 2 длиной 1
    s1 = "ab";
    s2 = "a";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 3 failed");
    }
    // тест 4. Строка 1 начинается из нескольких символов не из строки 2, строка 2 длиной 1
    s1 = "aab";
    s2 = "b";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 4 failed");
    }
    // тест 5. Строка 1 начинается с одного символа из строки 2
    s1 = "abb";
    s2 = "a";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 5 failed");
    }
    // тест 6. Две подстроки не из символа из строки 2 в строке 1, более длинная находится в начале
    s1 = "aabba";
    s2 = "b";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 6 failed");
    }
    // тест 7. Две подстроки из символа не из строки 2 в строке 1, более длинная находится в конце
    s1 = "abaaa";
    s2 = "b";
    if (strspn(s1, s2) != my_strspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 7 failed");
    }
    
    // тест 8. В начале строки 1 подстрока из символов не из строки 2, в строке 2 несколько символов
    s1 = "bbbaqf";
    s2 = "aqf";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 8 failed");
    }
    // тест 9. В строке 2 несколько символов, строка 1 начинается с символа, входящего в строку 2
    s1 = "abbdcq";
    s2 = "aqf";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 9 failed");
    }
    // тест 10. В строке 1 две подстроки из символов не из строки 2, при этом начальная короче
    s1 = "ccfabdd";
    s2 = "aqf";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 10 failed");
    }
    // тест 11. Строки состоят из одного символа, одинакового в обеих строках
    s1 = "a";
    s2 = "a";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 11 failed");
    }
    // тест 12. Строка 2 пуста
    s1 = "a";
    s2 = "";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 12 failed");
    }
    // тест 13. Строка 1 пуста
    s1 = "";
    s2 = "b";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 13 failed");
    }
    // тест 14. Обе строки пусты
    s1 = "";
    s2 = "";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 14 failed");
    }
    // тест 15. Обе строки из нескольких символов, в строке 1 все символы из строки 2
    s1 = "abc";
    s2 = "cab";
    if (strcspn(s1, s2) != my_strcspn(s1, s2))
    {
        failed_counter += 1;
        // puts("test 15 failed");
    }
    
    return failed_counter;
}


int test_strrchr(void)
{
    unsigned failed_counter = 0;
    char *s;
    char c;
    // puts("my_strrchr testing");
    // тест 1. Строка из одного символа, поиск того же символа
    s = "a";
    c = 'a';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 1 failed");
    }
    // тест 2. Строка из двух разных символов, поиск первого из них
    s = "ab";
    c = 'a';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 2 failed");
    }
    // тест 3. Строка из двух разных символов, поиск второго из них
    s = "ab";
    c = 'b';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        //puts("test 3 failed");
    }
    // тест 4. Поиск символа, встречающегося в строке единожды
    s = "abrakadabra";
    c = 'k';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 4 failed");
    }
    // тест 5. Поиск символа, встречающего в строке несколько раз
    s = "abrakadabra";
    c = 'b';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 5 failed");
    }
    // тест 6. Строка из нескольких одинаковых символов, поиск того же символа
    s = "aaaa";
    c = 'a';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 6 failed");
    }
    
    // тест 7. Строка из одного символа, поиск другого символа
    s = "a";
    c = 'b';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 7 failed");
    }
    // тест 8. Поиск нулевого символа
    s = "a";
    c = 0;
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 8 failed");
    }
    // тест 9. Пустая строка
    s = "";
    c = 'a';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 9 failed");
    }
    // тест 10. Строка из нескольких символов, поиск символа, не встречающегося в строке
    s = "sad";
    c = 'k';
    if (strrchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 10 failed");
    }
    // тест 11. Поиск символа за пределами размера char
    s = "sad";
    int i = 128;
    if (strrchr(s, i) != my_strrchr(s, i))
    {
        failed_counter += 1;
        // puts("test 11 failed");
    }
    
    return failed_counter;
}


int test_strchr(void)
{
    unsigned failed_counter = 0;
    char *s;
    char c;
    // puts("my_strchr testing");
    // тест 1. Строка из одного символа, поиск того же символа
    s = "a";
    c = 'a';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 1 failed");
    }
    // тест 2. Строка из двух различных символов, поиск первого из них
    s = "ab";
    c = 'a';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 2 failed");
    }
    // тест 3. Строка из двух различных символов, поиск второго из них
    s = "ab";
    c = 'b';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 3 failed");
    }
    // тест 4. Поиск символа, встречающегося в строке единожды
    s = "abrakadabra";
    c = 'k';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 4 failed");
    }
    // тест 5. Поиск символа, встречающегося в строке несколько раз
    s = "abrakadabra";
    c = 'b';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 5 failed");
    }
    // тест 6. Строка из нескольких одинаковых символов, поиск того же символа
    s = "aaaa";
    c = 'a';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 6 failed");
    }
    
    // тест 7. Строка из одного символа, поиск другого
    s = "a";
    c = 'b';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 7 failed");
    }
    // тест 8. Поиск нулевого символа
    s = "a";
    c = 0;
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 8 failed");
    }
    // тест 9. Пустая строка
    s = "";
    c = 'a';
    if (strchr(s, c) != my_strchr(s, c))
    {
        failed_counter += 1;
        // puts("test 9 failed");
    }
    // тест 10. Строка из нескольких символов, поиск символа, не встречающегося в строке
    s = "sad";
    c = 'k';
    if (strchr(s, c) != my_strrchr(s, c))
    {
        failed_counter += 1;
        // puts("test 10 failed");
    }
    // тест 11. Поиск символа вне границ типа char
    s = "sad";
    int i = 128;
    if (strchr(s, i) != my_strchr(s, i))
    {
        failed_counter += 1;
        // puts("test 11 failed");
    }
    
    return failed_counter;
}


int test_all(void)
{
    unsigned failed_counter = 0;
    
    failed_counter += test_strpbrk();
    
    failed_counter += test_strspn();
    
    failed_counter += test_strcspn();
    
    failed_counter += test_strchr();
    
    failed_counter += test_strrchr();
    
    return failed_counter;
}
