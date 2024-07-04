
#include "string_alg.h"
#include<iostream>

namespace String
{

    // Алгоритм поиска по образцу с помощью конечного автомата
    // 
    // 
    // 
    // Функция для вычисления таблицы переходов
    std::vector<int> StrAlgorithms::computeTransitionTable(const std::string& pattern)
    {
        int m = pattern.size();// Получаем длину шаблона
        std::vector<int> transition(m + 1, 0);// Создаем вектор для таблицы переходов, и заполняем его нулями
        transition[0] = -1;// Инициализируем первый элемент таблицы переходов значением -1
        int k = -1;// Инициализируем переменную k значением -1

        // Цикл по длине шаблона
        for (int q = 1; q <= m; ++q)
        {
            while (k >= 0 && pattern[k] != pattern[q - 1]) // Пока k >= 0 и символы не совпадают
            {
                k = transition[k];// Уменьшаем k до значения из таблицы переходов
            }
            k++;// Увеличиваем k
            transition[q] = k;// Записываем значение k в таблицу переходов
        }
        return transition; // Возвращаем таблицу переходов
    }

    // Функция для поиска подстроки в тексте
    void StrAlgorithms::searchPattern(const std::string& text, const std::string& pattern)
    {
        int n = text.size();// Получаем длину текста
        int m = pattern.size();// Получаем длину шаблона
        std::vector<int> transition = computeTransitionTable(pattern);// Получаем таблицу переходов для указанного шаблона

        int q = 0; // Инициализируем переменную q значением 0

        // Цикл по всем символам текста
        for (int i = 0; i < n; ++i)
        {
            while (q >= 0 && pattern[q] != text[i]) // Пока q >= 0 и символы не совпадают
            {
                q = transition[q]; // Уменьшаем q до значения из таблицы переходов
            }

            // Обновление значения
            q++;// Увеличиваем q
            if (q == m) // Если найден шаблон
            {
                std::cout << "Pattern found at index " << i - m + 1 << std::endl;// Выводим индекс найденного шаблона
                q = transition[q];// Возврат к начальному значению
            }
        }
    }


    // Алгоритм Кнута - Морриса - Пратта для поиска по образцу
    // 
    // 
    // 
    // Функция для вычисления префикс-функции
//(Находим вектор мксимально совпавших префиксов и суффиксов в шаблоне)
    std::vector<int> StrAlgorithms::KMP(const std::string& pattern)
    {
        std::vector<int> arr(pattern.size(), 0);//создание вектора arr, размер которого равен размеру шаблона, заполненного нулями.
        int i = 1, j = 0;//Определяем индесы i и j (j-префикс, i-суффикс)

        //Проходим по всему шаблону
        while (i < pattern.size())
        {

            //Если префикс и суффикс совпали 
            if (pattern[j] == pattern[i])
            {
                arr[i] = j + 1;//Записываем в вектор длинну совпавшей части 
                i++; j++;//Увиличиваем i и j 
            }

            //Если префикс и суффикс не совпали
            else
            {
                //И если j индекс равен 0
                if (j == 0)
                {
                    arr[i] = 0;//Значение в масиве меняем на ноль 
                    i++;//увиличиваем i
                }

                //Если j индекс не равен 0 
                else
                {
                    j = arr[j - 1];// Обновляем j значением из вектора arr на позиции j - 1
                }
            }
        }
        return arr;// Возвращаем вектор префикс-функции	
    }

    // Функция для поиска подстроки в тексте с использованием алгоритма Кнута-Морриса-Пратта
    void StrAlgorithms::searchPatternn(const std::string& text, const std::string& pattern)
    {
        int n = text.size();// Получаем длину текста
        int m = pattern.size();// Получаем длину шаблона
        std::vector<int> p = KMP(pattern);// Получаем вектор префикс-функции для шаблона
        int i = 0, j = 0, check = 0;// Инициализируем переменные i, j и check

        // Пока не достигнут конец текста
        while (i < n)
        {
            // Если символ на позиции i в тексте совпадает с символом на позиции j в шаблоне
            if (text[i] == pattern[j])
            {
                i++; j++;// Увеличиваем значения i и j
                if (j == m) // Если j достигло конца шаблона
                {
                    check = 1;// Устанавливаем флаг check в 1
                    std::cout << "Pattern found at index " << i - m << std::endl;// Выводим информацию о найденном шаблоне
                }
            }

            // Если символ на позиции i в тексте не совпадает с символом на позиции j в шаблоне
            else
            {
                if (j > 0)//Если j больше 0
                {
                    j = p[j - 1];// Обновляем j значением из вектора p на позиции j - 1
                }

                //в противном случае 
                else
                {
                    i++;// Увеличиваем i
                }
            }

            // Если прошли весь текст и шаблон не был найден
            if (i == n && !check)
            {
                std::cout << "There is no pattern in the text " << std::endl;// Выводим информацию о том, что шаблон не найден
            }
        }

    }


    // Алгоритм Бойера - Мура для поиска по образцу
    // 
    // 
    // 
    // Функция для создания таблицы смещений
    std::map<char, int> StrAlgorithms::displaced(const std::string& pattern)
    {
        //Начинам c n-1 
        //Берем значение которое наиболее близко к концу образа 

            // Множество уникальных символов
        std::set<char> uniqueChars;
        // Карта смещений
        std::map<char, int> displaceMap;
        // Размер шаблона
        int p_size = pattern.size() - 1;
        // Проход по шаблону для заполнения карты смещений
        for (int i = p_size - 1; i >= 0; i--)
        {
            // Если символ уникален
            if (uniqueChars.find(pattern[i]) == uniqueChars.end())
            {
                uniqueChars.insert(pattern[i]);// Добавляем символ в множество уникальных символов
                displaceMap.insert(std::make_pair(pattern[i], p_size - i));// Рассчитываем смещение для данного символа
            }
        }

        // Обработка последнего символа шаблона
        if (uniqueChars.find(pattern[p_size]) == uniqueChars.end())
        {
            // Если последний символ уникален
            displaceMap.insert(std::make_pair(pattern[p_size], p_size + 1));// Добавляем символ в множество уникальных символов
        }

        // Добавление смещения для символа-заполнителя ('*')
        displaceMap.insert(std::make_pair('*', p_size + 1));
        return displaceMap;//Возвращаем карту смещений 
    }

    // Основной алгоритм BMH
    void StrAlgorithms::algorithmBMH(const std::string& text, const std::string& pattern)
    {
        int n = text.size();// Длина строки
        int m = pattern.size();// Длина шаблона
        std::map<char, int> p = displaced(pattern);// Получение таблицы смещений для шаблона

        int i = m - 1, check = 0;// Инициализация индекса

        // Пока индекс не выйдет за границы строки
        while (i < n)
        {
            int k = 0;// Счетчик совпадений
            int j = m - 1;// Индекс в шаблоне

            // Сравниваем символы справа налево
            while (j >= 0 && pattern[j] == text[i - k])
            {
                j--;
                k++;
            }

            // Если все символы совпали
            if (j == -1)
            {
                check = 1;// Помечаем, что вхождение найдено
                std::cout << "Pattern found at index " << i - m + 1 << std::endl;// Выводим позицию начала вхождения
            }

            // Рассчитываем смещение с учетом текущего символа текста
            if (p.find(text[i]) == p.end())
            {
                // Если символ не найден в таблице смещений
                // Сдвигаемся на размер шаблона
                i += p['*'];
            }
            else
            {
                // Если символ найден в таблице смещений
                // Сдвигаемся на значение смещения
                i += p[text[i]];
            }
        }

        // Если вхождение не найдено
        if (!check)
        {
            std::cout << "There is no pattern in the text " << std::endl;
        }
    }


    // Алгоритм Рабина для поиска по образцу
    // 
    // 
    // 
    // Функция для вычисления хеша строки
    unsigned long long StrAlgorithms::calculateHash(const std::string& str, int start, int end, int prime)
    {
        unsigned long long hashValue = 0; // Инициализация переменной для хранения хеш-значения.
        for (int i = start; i <= end; ++i) // Цикл перебора символов строки в заданном диапазоне.
        {
            hashValue = (hashValue * prime + (int)str[i]) % prime;// Вычисление хеш-значения для текущего символа.
        }
        return hashValue;// Возврат вычисленного хеш-значения.
    }

    // Функция поиска подстроки с использованием алгоритма Рабина-Карпа
    void StrAlgorithms::searchRabinKarp(const std::string& text, const std::string& pattern, int prime)
    {
        int n = text.length();// Длина текста.
        int m = pattern.length();// Длина образца.
        int p = prime;// Простое число для вычисления хеша.

        // Вычисление хешей для образца и текста
        unsigned long long patternHash = calculateHash(pattern, 0, m - 1, p);// Вычисление хеша для образца.
        unsigned long long textHash = calculateHash(text, 0, m, p);// Вычисление хеша для начальной подстроки текста.

        // Проход по тексту и сравнение хешей
        for (int i = 0; i <= n - m; ++i) // Цикл по тексту для сравнения хешей образца и подстроки текста.
        {
            if (patternHash == textHash) // Если хеши совпали.
            {
                bool check = true;// Переменная для проверки совпадения символов.
                for (int j = 0; j < m; ++j) // Цикл для проверки совпадения символов образца и текста.
                {
                    if (text[i + j] != pattern[j]) // Если символы не совпадают.
                    {
                        check = false;// Установка флага неполного совпадения.
                    }
                }
                if (check) // Если все символы совпадают.
                {
                    std::cout << "Pattern found at index " << i << std::endl;// Вывод индекса найденного образца.
                }
            }

            // Обновление хеша для следующей итерации
            if (i < n - m) // Если не достигнут конец текста.
            {
                textHash = (textHash - (int)text[i] + p) % p; // Обновление хеш-значения для следующей подстроки текста.
                textHash = (textHash * prime + (int)text[i + m]) % p;// Пересчет хеша для следующей итерации.
            }
        }
    }


   




}