#pragma once

#include <iostream>
#include <vector>


namespace Sorting
{
    class Sorts
    {
    public:
        // Сортировка пузырьком
        static void bubbleSort(std::vector<int>& sequence);

        // Функция сортировки методом "Вставки"
        static void insertionSort(std::vector<int>& sequence);

        // Cортировка Посредством выбора
        static void selectionSort(std::vector<int>& arr);



        // Cортировка Шелла
        static void shellSort(std::vector<int>& arr);



        // Быстрая сортировка
        static void quickSort(int arr[], int start, int end);
        static int partition(int arr[], int start, int end);


        // Корневая сортировка
        static int findMax(int arr[], int n);
        static void countSort(int arr[], int n, int exp);
        static void radixSort(int arr[], int n);

    };
}