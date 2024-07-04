#include "include\sorting_alg.h"
#include "include\string_alg.h"
#include "include\graph_alg.h"
#include "include\search_alg.h"
#include <iostream>


void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
}

void printArray(std::vector<int> arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
}



int main()
{
	//Sorting algorithms
	std::cout << "SORTING ALGORITHMS: " << std::endl << std::endl;

	std::vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };
	int n = 7;
	Sorting::Sorts::bubbleSort(arr);
	std::cout << "Bubble Sort: ";
	printArray(arr, n);
	std::cout << std::endl;
	

	std::vector<int> arr1 = { 64, 34, 25, 12, 22, 11, 90 };
	Sorting::Sorts::insertionSort(arr1);
	std::cout << "InsertionSort: ";
	printArray(arr1, n);
	std::cout << std::endl;


	std::vector<int> arr2 = { 64, 34, 25, 12, 22, 11, 90 };
	Sorting::Sorts::selectionSort(arr2);
	std::cout << "SelectionSort: ";
	printArray(arr2, n);
	std::cout << std::endl;


	std::vector<int> arr3 = { 64, 34, 25, 12, 22, 11, 90 };
	Sorting::Sorts::shellSort(arr3);
	std::cout << "ShellSort: ";
	printArray(arr3, n);
	std::cout << std::endl;

	
	int arr4[] = { 64, 34, 25, 12, 22, 11, 90 };
	Sorting::Sorts::quickSort(arr4, 0, n - 1);
	std::cout << "QuickSort: ";
	printArray(arr4, n);
	std::cout << std::endl;


	int arr5[] = { 64, 34, 25, 12, 22, 11, 90 };
	Sorting::Sorts::radixSort(arr5, n);
	std::cout << "RadixSort: ";
	printArray(arr5, n);
	std::cout << std::endl << std::endl << std::endl;



	//String algorithms
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "STRING ALGORITHMS: " << std::endl << std::endl;
	
	std::string text = "ababcababcabcabc";
	std::string pattern = "abcabc";
	int prime = 111;

	std::cout << "Finite-state machine: " << std::endl;
	String::StrAlgorithms::searchPattern(text, pattern);// Алгоритм поиска по образцу с помощью конечного автомата
	std::cout << std::endl;

	std::cout << "KMP: " << std::endl;
	String::StrAlgorithms::searchPatternn(text, pattern); // Алгоритм Кнута - Морриса - Пратта для поиска по образцу
	std::cout << std::endl;

	std::cout << "BMH: " << std::endl;
	String::StrAlgorithms::algorithmBMH(text, pattern); // Алгоритм Бойера - Мура для поиска по образцу
	std::cout << std::endl;

	std::cout << "RabinKarp: " << std::endl;
	String::StrAlgorithms::searchRabinKarp(text, pattern, prime); // Алгоритм Рабина для поиска по образцу
	std::cout << std::endl << std::endl;

	
	//Search algorithms
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "SEARCH ALGORITHMS: " << std::endl << std::endl;

	std::vector<int> arr6 = { 11, 22, 25, 34, 64, 90 };
	int index = Search::Search::linearSearch(arr6, 90);
	std::cout << "Linear Search: " << "number 90 found at index " << index << std::endl;

	
	int index1 = Search::Search::binarySearch(arr6, 22, 0, arr6.size() - 1);
	std::cout << "Binary Search: " << "number 22 found at index " << index1 << std::endl;

	
	int index2 = Search::Search::jumpSearch(arr6, 25);
	std::cout << "Jump Search: " << "number 25 found at index " << index2 << std::endl;
	std::cout << std::endl << std::endl;


	//Graph algorithms
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "GRAPH ALGORITHMS: " << std::endl << std::endl;
	
	std::vector<std::vector<int>> adjacencyMatrix = {
		{ 0, 10, 10, 0, 0, 0 },
		{ 10, 0, 0, 4, 1, 0 },
		{ 10, 0, 0, 6, 0, 0 },
		{ 0, 4, 6, 0, 11, 0 },
		{ 0, 1, 0, 11, 0, 1 },
		{ 0, 0, 0, 0, 1, 0 }
	};
	Graph::Graph<int> graph(adjacencyMatrix);

	// Обход графа в ширину
	std::vector<int> bfsResult = graph.bfs(0);
	std::cout << "BFS from vertex 0: ";
	for (const auto& elem : bfsResult) 
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;


	// Метод обхода графа в глубину
	std::vector<int> dfsResult = graph.dfs(0);
	std::cout << "DFS from vertex 0: ";
	for (const auto& elem : dfsResult) 
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	//Алгоритм Дейкстры поиска кратчайших путей из одной вершины
	std::vector<int> dijkstraResult = graph.dijkstra(0);
	std::cout << "Dijkstra's algorithm from vertex 0: ";
	for (const auto& elem : dijkstraResult) 
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	//Алгоритм Беллмана-Форда поиска кратчайших путей из одной вершины
	std::vector<int> bellmanFordResult = graph.bellmanFord(0);
	std::cout << "Bellman-Ford algorithm from vertex 0: ";
	for (const auto& elem : bellmanFordResult) 
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	//Эйлеров цикл
	bool hasEulerian = graph.hasEulerianCycle();
	if (hasEulerian) 
	{
		std::cout << "Eulerian Cycle: ";
		graph.printEulerianCycle();
	}
	else
	{
		std::cout << "There is no Eulerian Cycle" << std::endl << std::endl;
	}
	std::cout << "---------------------------------------------------------" << std::endl;



}