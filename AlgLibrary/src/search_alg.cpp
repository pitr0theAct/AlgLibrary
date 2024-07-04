#include "search_alg.h"
#include <cmath>
#include <string>

namespace Search
{
    int Search::linearSearch(const std::vector<int>& arr, int key) 
    {
        for (size_t i = 0; i < arr.size(); i++) 
        {
            if (arr[i] == key) // ���� ������� ������� ����� �������� �����
            { 
                return i; // ���������� ������ ���������� ��������
            }
        }
        return -1; // ���� ������� �� ������, ���������� -1
    }

    int Search::binarySearch(const std::vector<int>& arr, int key, int left, int right) 
    {
        while (left <= right) // ���� ����� ������� �� ��������� ������
        { 
            int mid = left + (right - left) / 2; // ��������� ������� ������
            if (arr[mid] == key) // ���� ������� ������� ����� �������� �����
            { 
                return mid; // ���������� ������ ���������� ��������
            }
            if (arr[mid] < key) // ���� ������� ������� ������ �������� �����
            { 
                left = mid + 1; // �������� ����� ������� ������
            }
            else // ���� ������� ������� ������ �������� �����
            { 
                right = mid - 1; // �������� ������ ������� �����
            }
        }
        return -1; // ���� ������� �� ������, ���������� -1
    }

    int Search::jumpSearch(const std::vector<int>& arr, int key) 
    {
        int n = arr.size(); // �������� ������ �������
        int step = std::sqrt(n); // ��������� ������ ���� ��� �������
        int prev = 0; // �������������� ���������� �������

        while (arr[std::min(step, n) - 1] < key) // ���� ������� �� ������� ���� ������ �������� �����
        { 
            prev = step; // ��������� ���������� �������
            step += std::sqrt(n); // ����������� ���
            if (prev >= n) // ���� ���������� ������� ��������� ������ �������
            { 
                return -1; // ������� �� ������, ���������� -1
            }
        }

        for (int i = prev; i < std::min(step, n); i++) // �������� ����� � ��������� [prev, step)
        { 
            if (arr[i] == key) // ���� ������� ������� ����� �������� �����
            { 
                return i; // ���������� ������ ���������� ��������
            }
        }

        return -1; // ���� ������� �� ������, ���������� -1
    }

}