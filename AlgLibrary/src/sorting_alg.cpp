
#include "sorting_alg.h"
#include<iostream>

namespace Sorting
{
    //Сортировка пузырьком
    void Sorts::bubbleSort(std::vector<int>& sequence)
    {
        int n = sequence.size(); // Размер последовательности чисел

        for (int i = 0; i < n - 1; i++)
        { // Внешний цикл для прохода по элементам
            for (int j = 0; j < n - 1 - i; j++)
            { // Внутренний цикл для сравнения и обмена элементов
                if (sequence[j] > sequence[j + 1])
                { // Если текущий элемент больше следующего
                    std::swap(sequence[j], sequence[j + 1]); // Обмен элементов
                }
            }
        }
    }



    // Функция сортировки методом "Вставки"
    void Sorts::insertionSort(std::vector<int>& sequence)
    {
        int n = sequence.size();// Переменная n содержит размер входной последовательности для сортировки

        for (int i = 1; i < n; i++)// Цикл for выполняется для каждого элемента последовательности, начиная со второго
        {
            int key = sequence[i]; // Текущий элемент, который нужно вставить в отсортированную последовательность
            int j = i - 1;// Инициализация переменной j для перемещения элементов, больших key, вперед

            // Перемещение элементов, больших key, вперед
            while (j >= 0 && sequence[j] > key)
            {
                sequence[j + 1] = sequence[j];
                j--;
            }

            sequence[j + 1] = key; // Вставка текущего элемента в правильную позицию
        }
    }



    //Cортировка Посредством выбора
    void Sorts::selectionSort(std::vector<int>& arr)
    {
        int n = arr.size();//определение переменной n как размера входного массива.

        for (int i = 0; i < n - 1; i++)//цикл, который проходит по всем элементам массива, кроме последнего.
        {
            int minIndex = i;//инициализация переменной minIndex текущим индексом.

            // Находим индекс наименьшего элемента в оставшейся части массива
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[minIndex]) //условие, проверяющее, является ли текущий элемент минимальным.
                {
                    minIndex = j;//обновление минимального индекса, если текущий элемент меньше минимального.
                }
            }

            // Меняем местами текущий элемент с наименьшим элементом
            std::swap(arr[minIndex], arr[i]);
        }
    }



    // Cортировка Шелла
    void Sorts::shellSort(std::vector<int>& arr)
    {
        int n = arr.size();// Определяем размер входного массива

        for (int gap = n / 2; gap > 0; gap /= 2)// Внешний цикл для определения размера промежутка между элементами, начинаем 
            //с половины размера массива и уменьшаем промежуток в два раза на каждой итерации
        {
            for (int i = gap; i < n; ++i)// Внутренний цикл для перебора всех элементов массива
            {
                int temp = arr[i];// Сохраняем текущий элемент во временную переменную temp
                int j;// Берем индекс j равный i и выполняем сравнение с элементами, находящимися на gap-интервале

                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)// Если элемент arr[j - gap] больше temp, то сдвигаем элемент на gap позиций вправо
                {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;// Присваиваем temp элементу с индексом j
            }
        }
    }



    // Быстрая сортировка
    int Sorts::partition(int arr[], int start, int end)// Функция partition для быстрой сортировки принимает массив, начальный и конечный индексы
    {
        int pivot = arr[start];// Выбираем опорный элемент в качестве первого элемента массива

        // Считаем количество элементов меньше или равных опорному
        int count = 0;
        for (int i = start + 1; i <= end; i++)
        {
            if (arr[i] <= pivot)
                count++;
        }

        // Индекс опорного элемента после перестановки
        int pivotIndex = start + count;
        std::swap(arr[pivotIndex], arr[start]);

        // Разделение элементов массива относительно опорного
        int i = start, j = end;
        while (i < pivotIndex && j > pivotIndex)
        {
            // Поиск элементов для перестановки
            while (arr[i] <= pivot)
            {
                i++;
            }

            while (arr[j] > pivot)
            {
                j--;
            }

            // Перестановка элементов
            if (i < pivotIndex && j > pivotIndex)
            {
                std::swap(arr[i++], arr[j--]);
            }
        }

        return pivotIndex;// Возвращаем индекс опорного элемента после сортировки
    }

    void Sorts::quickSort(int arr[], int start, int end)
    {
        // Базовый случай - массив из одного элемента
        if (start >= end)
            return;

        // Разделение на подмассивы и рекурсивная сортировка
        int p = partition(arr, start, end);

        quickSort(arr, start, p - 1);

        quickSort(arr, p + 1, end);
    }



    // Корневая сортировка

    // Функция для нахождения максимального элемента
    int Sorts::findMax(int arr[], int n)
    {
        int maxElement = arr[0];
        for (int i = 1; i < n; i++)
        {
            if (arr[i] > maxElement)
            {
                maxElement = arr[i];
            }
        }
        return maxElement;
    }

    // Функция для сортировки массива по указанному разряду
    void Sorts::countSort(int arr[], int n, int exp)
    {
        const int RANGE = 10; // Диапазон чисел (0-9)
        int* output = new int[n];// Вспомогательный массив для сохранения отсортированного массива(Динамическое выделение памяти)
        int count[RANGE] = { 0 };// Массив для хранения количества элементов с определенными разрядами

        // Подсчитываем количество элементов с определенными разрядами
        for (int i = 0; i < n; i++)
        {
            count[(arr[i] / exp) % 10]++;
        }

        // Преобразуем count[i] так, чтобы count[i] содержал фактическую позицию
        // данного разряда в отсортированном массиве output[]
        for (int i = 1; i < RANGE; i++)
        {
            count[i] += count[i - 1];

        }

        // Строим отсортированный массив
        for (int i = n - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Копируем отсортированный массив output в исходный массив arr
        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }

        delete[] output;//Отчистка памяти 
    }

    // Функция для сортировки массива методом корневой сортировки
    void Sorts::radixSort(int arr[], int n)
    {
        // Находим максимальное число для определения количества разрядов
        int maxElement = findMax(arr, n);

        // Сортировка массива по каждому разряду
        for (int exp = 1; maxElement / exp > 0; exp *= 10)
        {
            countSort(arr, n, exp);
        }
    }




}