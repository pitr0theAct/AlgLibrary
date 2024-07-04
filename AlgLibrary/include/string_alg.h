#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

namespace String
{
	class StrAlgorithms
	{
	public:
		
		// �������� ������ �� ������� � ������� ��������� ��������
		static std::vector<int> computeTransitionTable(const std::string& pattern);
		static void searchPattern(const std::string& text, const std::string& pattern);

		// �������� ����� - ������� - ������ ��� ������ �� �������
		static std::vector<int> KMP(const std::string& pattern);
		static void searchPatternn(const std::string& text, const std::string& pattern);

		// �������� ������ - ���� ��� ������ �� �������
		static std::map<char, int> displaced(const std::string& pattern);
		static void algorithmBMH(const std::string& text, const std::string& pattern);

		// �������� ������ ��� ������ �� �������
		static unsigned long long calculateHash(const std::string& str, int start, int end, int prime);
		static void searchRabinKarp(const std::string& text, const std::string& pattern, int prime);

	};
}