#pragma once

#include <iostream>
#include <vector>


namespace Sorting
{
    class Sorts
    {
    public:
        // ���������� ���������
        static void bubbleSort(std::vector<int>& sequence);

        // ������� ���������� ������� "�������"
        static void insertionSort(std::vector<int>& sequence);

        // C��������� ����������� ������
        static void selectionSort(std::vector<int>& arr);



        // C��������� �����
        static void shellSort(std::vector<int>& arr);



        // ������� ����������
        static void quickSort(int arr[], int start, int end);
        static int partition(int arr[], int start, int end);


        // �������� ����������
        static int findMax(int arr[], int n);
        static void countSort(int arr[], int n, int exp);
        static void radixSort(int arr[], int n);

    };
}