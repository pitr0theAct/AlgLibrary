
#include "string_alg.h"
#include<iostream>

namespace String
{

    // �������� ������ �� ������� � ������� ��������� ��������
    // 
    // 
    // 
    // ������� ��� ���������� ������� ���������
    std::vector<int> StrAlgorithms::computeTransitionTable(const std::string& pattern)
    {
        int m = pattern.size();// �������� ����� �������
        std::vector<int> transition(m + 1, 0);// ������� ������ ��� ������� ���������, � ��������� ��� ������
        transition[0] = -1;// �������������� ������ ������� ������� ��������� ��������� -1
        int k = -1;// �������������� ���������� k ��������� -1

        // ���� �� ����� �������
        for (int q = 1; q <= m; ++q)
        {
            while (k >= 0 && pattern[k] != pattern[q - 1]) // ���� k >= 0 � ������� �� ���������
            {
                k = transition[k];// ��������� k �� �������� �� ������� ���������
            }
            k++;// ����������� k
            transition[q] = k;// ���������� �������� k � ������� ���������
        }
        return transition; // ���������� ������� ���������
    }

    // ������� ��� ������ ��������� � ������
    void StrAlgorithms::searchPattern(const std::string& text, const std::string& pattern)
    {
        int n = text.size();// �������� ����� ������
        int m = pattern.size();// �������� ����� �������
        std::vector<int> transition = computeTransitionTable(pattern);// �������� ������� ��������� ��� ���������� �������

        int q = 0; // �������������� ���������� q ��������� 0

        // ���� �� ���� �������� ������
        for (int i = 0; i < n; ++i)
        {
            while (q >= 0 && pattern[q] != text[i]) // ���� q >= 0 � ������� �� ���������
            {
                q = transition[q]; // ��������� q �� �������� �� ������� ���������
            }

            // ���������� ��������
            q++;// ����������� q
            if (q == m) // ���� ������ ������
            {
                std::cout << "Pattern found at index " << i - m + 1 << std::endl;// ������� ������ ���������� �������
                q = transition[q];// ������� � ���������� ��������
            }
        }
    }


    // �������� ����� - ������� - ������ ��� ������ �� �������
    // 
    // 
    // 
    // ������� ��� ���������� �������-�������
//(������� ������ ���������� ��������� ��������� � ��������� � �������)
    std::vector<int> StrAlgorithms::KMP(const std::string& pattern)
    {
        std::vector<int> arr(pattern.size(), 0);//�������� ������� arr, ������ �������� ����� ������� �������, ������������ ������.
        int i = 1, j = 0;//���������� ������ i � j (j-�������, i-�������)

        //�������� �� ����� �������
        while (i < pattern.size())
        {

            //���� ������� � ������� ������� 
            if (pattern[j] == pattern[i])
            {
                arr[i] = j + 1;//���������� � ������ ������ ��������� ����� 
                i++; j++;//����������� i � j 
            }

            //���� ������� � ������� �� �������
            else
            {
                //� ���� j ������ ����� 0
                if (j == 0)
                {
                    arr[i] = 0;//�������� � ������ ������ �� ���� 
                    i++;//����������� i
                }

                //���� j ������ �� ����� 0 
                else
                {
                    j = arr[j - 1];// ��������� j ��������� �� ������� arr �� ������� j - 1
                }
            }
        }
        return arr;// ���������� ������ �������-�������	
    }

    // ������� ��� ������ ��������� � ������ � �������������� ��������� �����-�������-������
    void StrAlgorithms::searchPatternn(const std::string& text, const std::string& pattern)
    {
        int n = text.size();// �������� ����� ������
        int m = pattern.size();// �������� ����� �������
        std::vector<int> p = KMP(pattern);// �������� ������ �������-������� ��� �������
        int i = 0, j = 0, check = 0;// �������������� ���������� i, j � check

        // ���� �� ��������� ����� ������
        while (i < n)
        {
            // ���� ������ �� ������� i � ������ ��������� � �������� �� ������� j � �������
            if (text[i] == pattern[j])
            {
                i++; j++;// ����������� �������� i � j
                if (j == m) // ���� j �������� ����� �������
                {
                    check = 1;// ������������� ���� check � 1
                    std::cout << "Pattern found at index " << i - m << std::endl;// ������� ���������� � ��������� �������
                }
            }

            // ���� ������ �� ������� i � ������ �� ��������� � �������� �� ������� j � �������
            else
            {
                if (j > 0)//���� j ������ 0
                {
                    j = p[j - 1];// ��������� j ��������� �� ������� p �� ������� j - 1
                }

                //� ��������� ������ 
                else
                {
                    i++;// ����������� i
                }
            }

            // ���� ������ ���� ����� � ������ �� ��� ������
            if (i == n && !check)
            {
                std::cout << "There is no pattern in the text " << std::endl;// ������� ���������� � ���, ��� ������ �� ������
            }
        }

    }


    // �������� ������ - ���� ��� ������ �� �������
    // 
    // 
    // 
    // ������� ��� �������� ������� ��������
    std::map<char, int> StrAlgorithms::displaced(const std::string& pattern)
    {
        //������� c n-1 
        //����� �������� ������� �������� ������ � ����� ������ 

            // ��������� ���������� ��������
        std::set<char> uniqueChars;
        // ����� ��������
        std::map<char, int> displaceMap;
        // ������ �������
        int p_size = pattern.size() - 1;
        // ������ �� ������� ��� ���������� ����� ��������
        for (int i = p_size - 1; i >= 0; i--)
        {
            // ���� ������ ��������
            if (uniqueChars.find(pattern[i]) == uniqueChars.end())
            {
                uniqueChars.insert(pattern[i]);// ��������� ������ � ��������� ���������� ��������
                displaceMap.insert(std::make_pair(pattern[i], p_size - i));// ������������ �������� ��� ������� �������
            }
        }

        // ��������� ���������� ������� �������
        if (uniqueChars.find(pattern[p_size]) == uniqueChars.end())
        {
            // ���� ��������� ������ ��������
            displaceMap.insert(std::make_pair(pattern[p_size], p_size + 1));// ��������� ������ � ��������� ���������� ��������
        }

        // ���������� �������� ��� �������-����������� ('*')
        displaceMap.insert(std::make_pair('*', p_size + 1));
        return displaceMap;//���������� ����� �������� 
    }

    // �������� �������� BMH
    void StrAlgorithms::algorithmBMH(const std::string& text, const std::string& pattern)
    {
        int n = text.size();// ����� ������
        int m = pattern.size();// ����� �������
        std::map<char, int> p = displaced(pattern);// ��������� ������� �������� ��� �������

        int i = m - 1, check = 0;// ������������� �������

        // ���� ������ �� ������ �� ������� ������
        while (i < n)
        {
            int k = 0;// ������� ����������
            int j = m - 1;// ������ � �������

            // ���������� ������� ������ ������
            while (j >= 0 && pattern[j] == text[i - k])
            {
                j--;
                k++;
            }

            // ���� ��� ������� �������
            if (j == -1)
            {
                check = 1;// ��������, ��� ��������� �������
                std::cout << "Pattern found at index " << i - m + 1 << std::endl;// ������� ������� ������ ���������
            }

            // ������������ �������� � ������ �������� ������� ������
            if (p.find(text[i]) == p.end())
            {
                // ���� ������ �� ������ � ������� ��������
                // ���������� �� ������ �������
                i += p['*'];
            }
            else
            {
                // ���� ������ ������ � ������� ��������
                // ���������� �� �������� ��������
                i += p[text[i]];
            }
        }

        // ���� ��������� �� �������
        if (!check)
        {
            std::cout << "There is no pattern in the text " << std::endl;
        }
    }


    // �������� ������ ��� ������ �� �������
    // 
    // 
    // 
    // ������� ��� ���������� ���� ������
    unsigned long long StrAlgorithms::calculateHash(const std::string& str, int start, int end, int prime)
    {
        unsigned long long hashValue = 0; // ������������� ���������� ��� �������� ���-��������.
        for (int i = start; i <= end; ++i) // ���� �������� �������� ������ � �������� ���������.
        {
            hashValue = (hashValue * prime + (int)str[i]) % prime;// ���������� ���-�������� ��� �������� �������.
        }
        return hashValue;// ������� ������������ ���-��������.
    }

    // ������� ������ ��������� � �������������� ��������� ������-�����
    void StrAlgorithms::searchRabinKarp(const std::string& text, const std::string& pattern, int prime)
    {
        int n = text.length();// ����� ������.
        int m = pattern.length();// ����� �������.
        int p = prime;// ������� ����� ��� ���������� ����.

        // ���������� ����� ��� ������� � ������
        unsigned long long patternHash = calculateHash(pattern, 0, m - 1, p);// ���������� ���� ��� �������.
        unsigned long long textHash = calculateHash(text, 0, m, p);// ���������� ���� ��� ��������� ��������� ������.

        // ������ �� ������ � ��������� �����
        for (int i = 0; i <= n - m; ++i) // ���� �� ������ ��� ��������� ����� ������� � ��������� ������.
        {
            if (patternHash == textHash) // ���� ���� �������.
            {
                bool check = true;// ���������� ��� �������� ���������� ��������.
                for (int j = 0; j < m; ++j) // ���� ��� �������� ���������� �������� ������� � ������.
                {
                    if (text[i + j] != pattern[j]) // ���� ������� �� ���������.
                    {
                        check = false;// ��������� ����� ��������� ����������.
                    }
                }
                if (check) // ���� ��� ������� ���������.
                {
                    std::cout << "Pattern found at index " << i << std::endl;// ����� ������� ���������� �������.
                }
            }

            // ���������� ���� ��� ��������� ��������
            if (i < n - m) // ���� �� ��������� ����� ������.
            {
                textHash = (textHash - (int)text[i] + p) % p; // ���������� ���-�������� ��� ��������� ��������� ������.
                textHash = (textHash * prime + (int)text[i + m]) % p;// �������� ���� ��� ��������� ��������.
            }
        }
    }


   




}