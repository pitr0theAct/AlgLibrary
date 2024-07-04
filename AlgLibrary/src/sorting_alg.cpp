
#include "sorting_alg.h"
#include<iostream>

namespace Sorting
{
    //���������� ���������
    void Sorts::bubbleSort(std::vector<int>& sequence)
    {
        int n = sequence.size(); // ������ ������������������ �����

        for (int i = 0; i < n - 1; i++)
        { // ������� ���� ��� ������� �� ���������
            for (int j = 0; j < n - 1 - i; j++)
            { // ���������� ���� ��� ��������� � ������ ���������
                if (sequence[j] > sequence[j + 1])
                { // ���� ������� ������� ������ ����������
                    std::swap(sequence[j], sequence[j + 1]); // ����� ���������
                }
            }
        }
    }



    // ������� ���������� ������� "�������"
    void Sorts::insertionSort(std::vector<int>& sequence)
    {
        int n = sequence.size();// ���������� n �������� ������ ������� ������������������ ��� ����������

        for (int i = 1; i < n; i++)// ���� for ����������� ��� ������� �������� ������������������, ������� �� �������
        {
            int key = sequence[i]; // ������� �������, ������� ����� �������� � ��������������� ������������������
            int j = i - 1;// ������������� ���������� j ��� ����������� ���������, ������� key, ������

            // ����������� ���������, ������� key, ������
            while (j >= 0 && sequence[j] > key)
            {
                sequence[j + 1] = sequence[j];
                j--;
            }

            sequence[j + 1] = key; // ������� �������� �������� � ���������� �������
        }
    }



    //C��������� ����������� ������
    void Sorts::selectionSort(std::vector<int>& arr)
    {
        int n = arr.size();//����������� ���������� n ��� ������� �������� �������.

        for (int i = 0; i < n - 1; i++)//����, ������� �������� �� ���� ��������� �������, ����� ����������.
        {
            int minIndex = i;//������������� ���������� minIndex ������� ��������.

            // ������� ������ ����������� �������� � ���������� ����� �������
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[minIndex]) //�������, �����������, �������� �� ������� ������� �����������.
                {
                    minIndex = j;//���������� ������������ �������, ���� ������� ������� ������ ������������.
                }
            }

            // ������ ������� ������� ������� � ���������� ���������
            std::swap(arr[minIndex], arr[i]);
        }
    }



    // C��������� �����
    void Sorts::shellSort(std::vector<int>& arr)
    {
        int n = arr.size();// ���������� ������ �������� �������

        for (int gap = n / 2; gap > 0; gap /= 2)// ������� ���� ��� ����������� ������� ���������� ����� ����������, �������� 
            //� �������� ������� ������� � ��������� ���������� � ��� ���� �� ������ ��������
        {
            for (int i = gap; i < n; ++i)// ���������� ���� ��� �������� ���� ��������� �������
            {
                int temp = arr[i];// ��������� ������� ������� �� ��������� ���������� temp
                int j;// ����� ������ j ������ i � ��������� ��������� � ����������, ������������ �� gap-���������

                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)// ���� ������� arr[j - gap] ������ temp, �� �������� ������� �� gap ������� ������
                {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;// ����������� temp �������� � �������� j
            }
        }
    }



    // ������� ����������
    int Sorts::partition(int arr[], int start, int end)// ������� partition ��� ������� ���������� ��������� ������, ��������� � �������� �������
    {
        int pivot = arr[start];// �������� ������� ������� � �������� ������� �������� �������

        // ������� ���������� ��������� ������ ��� ������ ��������
        int count = 0;
        for (int i = start + 1; i <= end; i++)
        {
            if (arr[i] <= pivot)
                count++;
        }

        // ������ �������� �������� ����� ������������
        int pivotIndex = start + count;
        std::swap(arr[pivotIndex], arr[start]);

        // ���������� ��������� ������� ������������ ��������
        int i = start, j = end;
        while (i < pivotIndex && j > pivotIndex)
        {
            // ����� ��������� ��� ������������
            while (arr[i] <= pivot)
            {
                i++;
            }

            while (arr[j] > pivot)
            {
                j--;
            }

            // ������������ ���������
            if (i < pivotIndex && j > pivotIndex)
            {
                std::swap(arr[i++], arr[j--]);
            }
        }

        return pivotIndex;// ���������� ������ �������� �������� ����� ����������
    }

    void Sorts::quickSort(int arr[], int start, int end)
    {
        // ������� ������ - ������ �� ������ ��������
        if (start >= end)
            return;

        // ���������� �� ���������� � ����������� ����������
        int p = partition(arr, start, end);

        quickSort(arr, start, p - 1);

        quickSort(arr, p + 1, end);
    }



    // �������� ����������

    // ������� ��� ���������� ������������� ��������
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

    // ������� ��� ���������� ������� �� ���������� �������
    void Sorts::countSort(int arr[], int n, int exp)
    {
        const int RANGE = 10; // �������� ����� (0-9)
        int* output = new int[n];// ��������������� ������ ��� ���������� ���������������� �������(������������ ��������� ������)
        int count[RANGE] = { 0 };// ������ ��� �������� ���������� ��������� � ������������� ���������

        // ������������ ���������� ��������� � ������������� ���������
        for (int i = 0; i < n; i++)
        {
            count[(arr[i] / exp) % 10]++;
        }

        // ����������� count[i] ���, ����� count[i] �������� ����������� �������
        // ������� ������� � ��������������� ������� output[]
        for (int i = 1; i < RANGE; i++)
        {
            count[i] += count[i - 1];

        }

        // ������ ��������������� ������
        for (int i = n - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // �������� ��������������� ������ output � �������� ������ arr
        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }

        delete[] output;//�������� ������ 
    }

    // ������� ��� ���������� ������� ������� �������� ����������
    void Sorts::radixSort(int arr[], int n)
    {
        // ������� ������������ ����� ��� ����������� ���������� ��������
        int maxElement = findMax(arr, n);

        // ���������� ������� �� ������� �������
        for (int exp = 1; maxElement / exp > 0; exp *= 10)
        {
            countSort(arr, n, exp);
        }
    }




}