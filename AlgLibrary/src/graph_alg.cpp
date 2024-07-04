#include "graph_alg.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <stack>
#include <cmath>

namespace Graph
{
    template<typename T>
    Graph<T>::Graph(int vertices) : vertices(vertices) //Конструктор
    {
        adjacencyMatrix.resize(vertices, std::vector<T>(vertices, 0));
    }

    Graph<int>::Graph(const std::vector<std::vector<int>>& adjacencyMatrix)
        : vertices(adjacencyMatrix.size()), adjacencyMatrix(adjacencyMatrix) {}

    //Метод для добовления ребра
    void Graph<int>::addEdge(int v, int w, int weight) 
    {
        // Добавляет ребро между вершинами v и w с весом weight
        adjacencyMatrix[v][w] = weight;
        adjacencyMatrix[w][v] = weight; // Для неориентированного графа
    }

    //Метод для реализации обхода в ширину 
    std::vector<int> Graph<int>::bfs(int start) 
    {
        // Реализация алгоритма обхода в ширину (BFS)
        std::vector<bool> visited(vertices, false); // Вектор для отслеживания посещенных вершин
        std::vector<int> result; // Вектор для хранения результата обхода
        std::queue<int> q; // Очередь для обхода вершин

        visited[start] = true; // Помечаем стартовую вершину как посещенную
        q.push(start); // Добавляем стартовую вершину в очередь

        while (!q.empty()) 
        {
            int v = q.front(); // Извлекаем вершину из очереди
            q.pop();
            result.push_back(v); // Добавляем вершину в результат обхода

            // Проходим по всем смежным вершинам
            for (int i = 0; i < vertices; ++i) 
            {
                // Если есть ребро между текущей вершиной и соседней, и соседняя вершина не посещена
                if (adjacencyMatrix[v][i] != 0 && !visited[i]) 
                {
                    visited[i] = true; // Помечаем соседнюю вершину как посещенную
                    q.push(i); // Добавляем соседнюю вершину в очередь
                }
            }
        }

        return result;
    }


    //Метод для реализации обхода в глубину
    std::vector<int> Graph<int>::dfs(int start) 
    {
        // Реализация алгоритма обхода в глубину (DFS)
        std::vector<bool> visited(vertices, false); // Вектор для отслеживания посещенных вершин
        std::vector<int> result; // Вектор для хранения результата обхода
        std::stack<int> s; // Стек для обхода вершин
        s.push(start); // Добавляем стартовую вершину в стек

        while (!s.empty()) // пока очередь не пуста
        {
            int v = s.top(); // Извлекаем вершину из стека
            s.pop();

            if (!visited[v]) 
            {
                visited[v] = true; // Помечаем вершину как посещенную
                result.push_back(v); // Добавляем вершину в результат обхода

                // Проходим по всем смежным вершинам в обратном порядке
                for (int i = vertices - 1; i >= 0; --i) 
                {
                    // Если есть ребро между текущей вершиной и соседней, и соседняя вершина не посещена
                    if (adjacencyMatrix[v][i] != 0 && !visited[i]) 
                    {
                        s.push(i); // Добавляем соседнюю вершину в стек
                    }
                }
            }
        }

        return result;
    }


    // Метод для нахождения кратчайшего пути методом Дейкстры
    std::vector<int> Graph<int>::dijkstra(int src) 
    {
        // Реализация алгоритма Дейкстры для поиска кратчайших путей от заданной вершины
        std::vector<int> dist(vertices, std::numeric_limits<int>::max()); // Вектор для хранения расстояний до вершин
        std::vector<bool> visited(vertices, false); // Вектор для отслеживания посещенных вершин
        dist[src] = 0; // Расстояние до исходной вершины равно 0

        for (int i = 0; i < vertices; ++i) 
        {
            int u = -1;
            // Находим вершину с минимальным расстоянием среди непосещенных вершин
            for (int j = 0; j < vertices; ++j)
            {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                {
                    u = j;
                }
            }

            // Если расстояние до вершины u равно бесконечности, то выходим из цикла
            if (dist[u] == std::numeric_limits<int>::max()) break;

            visited[u] = true; // Помечаем вершину u как посещенную

            // Обновляем расстояния до соседних вершин
            for (int v = 0; v < vertices; ++v) 
            {
                // Если есть ребро между вершинами u и v, и v не посещена,
                // и расстояние до v через u меньше текущего расстояния до v
                if (adjacencyMatrix[u][v] && !visited[v] && dist[u] + adjacencyMatrix[u][v] < dist[v]) 
                {
                    dist[v] = dist[u] + adjacencyMatrix[u][v]; // Обновляем расстояние до v
                }
            }
        }

        return dist; // Возвращаем вектор расстояний до вершин
    }


    // Алгоритм Беллмана-Форда для поиска кратчайших путей
    std::vector<int> Graph<int>::bellmanFord(int src) 
    {
        // Создаем вектор dist для хранения расстояний до вершин
        // Инициализируем все расстояния максимальным значением типа T
        std::vector<int> dist(vertices, std::numeric_limits<int>::max());

        // Устанавливаем расстояние до исходной вершины равным 0
        dist[src] = 0;

        // Выполняем (vertices - 1) итераций алгоритма Беллмана-Форда
        for (int i = 1; i < vertices; ++i) 
        {
            // Проходимся по всем ребрам графа
            for (int u = 0; u < vertices; ++u) 
            {
                for (int v = 0; v < vertices; ++v) 
                {
                    // Если существует ребро между вершинами u и v
                    // и расстояние до вершины u не бесконечно
                    // и новое расстояние до вершины v меньше текущего
                    if (adjacencyMatrix[u][v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjacencyMatrix[u][v] < dist[v]) 
                    {
                        // Обновляем расстояние до вершины v
                        dist[v] = dist[u] + adjacencyMatrix[u][v];
                    }
                }
            }
        }

        // Проверяем наличие отрицательных циклов
        for (int u = 0; u < vertices; ++u) 
        {
            for (int v = 0; v < vertices; ++v) 
            {
                // Если существует ребро между вершинами u и v
                // и расстояние до вершины u не бесконечно
                // и новое расстояние до вершины v меньше текущего
                if (adjacencyMatrix[u][v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjacencyMatrix[u][v] < dist[v]) 
                {
                    // Граф содержит отрицательный цикл
                    std::cerr << "Graph contains a negative-weight cycle" << std::endl;
                    // Возвращаем пустой вектор, указывающий на ошибку
                    return {};
                }
            }
        }

        // Возвращаем вектор кратчайших расстояний от исходной вершины до всех остальных вершин
        return dist;
    }


    //Структура вершины
    struct Edge 
    {
        int src, dest;
        int weight;
        bool operator<(const Edge& other) const 
        {
            return weight < other.weight;
        }
    };

    // Метод для нахождения корня дерева
    int Graph<int>::find(std::vector<int>& parent, int i) 
    {
        // Если родитель вершины i не равен самой вершине i
        if (parent[i] != i) 
        {
            // Рекурсивно находим корневую вершину для вершины i и обновляем родителя вершины i
            parent[i] = find(parent, parent[i]);
        }
        // Возвращаем родителя (корневую вершину) для вершины i
        return parent[i];
    }

    void Graph<int>::unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y) 
    {
        // Находим корневые вершины для вершин x и y
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        // Если ранг корневой вершины rootX меньше ранга корневой вершины rootY
        if (rank[rootX] < rank[rootY]) 
        {
            // Устанавливаем rootY в качестве родителя для rootX
            parent[rootX] = rootY;
        }
        // Если ранг корневой вершины rootX больше ранга корневой вершины rootY
        else if (rank[rootX] > rank[rootY]) 
        {
            // Устанавливаем rootX в качестве родителя для rootY
            parent[rootY] = rootX;
        }
        // Если ранги корневых вершин равны
        else 
        {
            // Устанавливаем rootX в качестве родителя для rootY
            parent[rootY] = rootX;
            // Увеличиваем ранг корневой вершины rootX на 1
            rank[rootX]++;
        }
    }


    // Метод для построения минимального остовного дерева (алгоритм Крускала)
    std::pair<int, std::vector<std::pair<int, int>>> Graph<int>::kruskal() 
    {
        // Создаем вектор ребер графа
        std::vector<Edge> edges;
        // Проходим по всем парам вершин в матрице смежности
        for (int u = 0; u < vertices; ++u) 
        {
            for (int v = u + 1; v < vertices; ++v) 
            {
                // Если между вершинами u и v есть ребро
                if (adjacencyMatrix[u][v]) 
                {
                    // Добавляем ребро в вектор ребер
                    edges.push_back({ u, v, adjacencyMatrix[u][v] });
                }
            }
        }

        // Сортируем вектор ребер по возрастанию веса
        std::sort(edges.begin(), edges.end());

        // Создаем вектор для хранения родителей вершин
        std::vector<int> parent(vertices);
        // Создаем вектор для хранения рангов вершин, инициализируем все ранги нулями
        std::vector<int> rank(vertices, 0);
        // Инициализируем каждую вершину как свою собственную родительскую вершину
        for (int i = 0; i < vertices; ++i) 
        {
            parent[i] = i;
        }

        // Переменная для хранения веса минимального остовного дерева
        int mstWeight = 0;
        // Вектор для хранения ребер минимального остовного дерева
        std::vector<std::pair<int, int>> mstEdges;
        // Проходим по всем ребрам в отсортированном векторе ребер
        for (const auto& edge : edges) 
        {
            // Находим корневые вершины для концов текущего ребра
            int rootX = find(parent, edge.src);
            int rootY = find(parent, edge.dest);

            // Если корневые вершины различны (ребро не образует цикл)
            if (rootX != rootY) 
            {
                // Добавляем вес текущего ребра к общему весу минимального остовного дерева
                mstWeight += edge.weight;
                // Объединяем множества, содержащие концы текущего ребра
                unionSets(parent, rank, rootX, rootY);
                // Добавляем текущее ребро в вектор ребер минимального остовного дерева
                mstEdges.push_back({ edge.src, edge.dest });
            }
        }

        // Возвращаем пару: вес минимального остовного дерева и вектор ребер минимального остовного дерева
        return { mstWeight, mstEdges };
    }


    // Метод который проверяет является ли граф эйлеровым
    bool Graph<int>::isEulerianCycle() 
    {
        // Проверяем, является ли граф связным
        if (!isConnected()) 
        {
            return false;
        }

        // Подсчитываем количество вершин с нечетной степенью
        int oddDegreeCount = 0;
        for (int i = 0; i < vertices; ++i) 
        {
            int degree = 0;
            for (int j = 0; j < vertices; ++j) 
            {
                if (adjacencyMatrix[i][j] != 0) 
                {
                    degree++;
                }
            }

            if (degree % 2 != 0) 
            {
                oddDegreeCount++;
            }
        }

        // Если количество вершин с нечетной степенью равно 0, граф является эйлеровым
        return oddDegreeCount == 0;
    }

    template<typename T>
    bool Graph<T>::isConnected() //Метод который проверяет является ли граф связным
    {
        // Создаем вектор для отслеживания посещенных вершин
        std::vector<bool> visited(vertices, false);
        // Создаем очередь для обхода в ширину
        std::queue<int> q;

        // Ищем первую вершину с ненулевой степенью
        int i;
        for (i = 0; i < vertices; ++i)
        {
            int degree = 0;
            for (int j = 0; j < vertices; ++j) 
            {
                if (adjacencyMatrix[i][j] != 0) 
                {
                    degree++;
                }
            }
            if (degree != 0) 
            {
                break;
            }
        }

        // Если все вершины имеют нулевую степень, граф считается связным
        if (i == vertices) 
        {
            return true;
        }

        // Начинаем обход в ширину с найденной вершины
        q.push(i);
        visited[i] = true;

        // Выполняем обход в ширину
        while (!q.empty()) 
        {
            int v = q.front();
            q.pop();

            // Обрабатываем соседние вершины
            for (int j = 0; j < vertices; ++j) 
            {
                if (adjacencyMatrix[v][j] && !visited[j]) 
                {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }

        // Проверяем, все ли вершины с ненулевой степенью были посещены
        for (int i = 0; i < vertices; ++i) 
        {
            int degree = 0;
            for (int j = 0; j < vertices; ++j) 
            {
                if (adjacencyMatrix[i][j] != 0) 
                {
                    degree++;
                }
            }

            if (degree != 0 && !visited[i]) 
            {
                return false;
            }
        }

        // Если все вершины с ненулевой степенью были посещены, граф связный
        return true;
    }


    bool Graph<int>::hasEulerianCycle() 
    {
        // Вызываем функцию isEulerianCycle для проверки наличия эйлерова цикла
        return isEulerianCycle();
    }

    
    void Graph<int>::eulerianUtil(int u, std::vector<std::vector<int>>& adj, std::vector<int>& path) 
    {
        // Обрабатываем все соседние вершины
        for (int v = 0; v < vertices; ++v)
        {
            if (adj[u][v]) 
            {
                // Удаляем ребро между вершинами u и v
                adj[u][v]--;
                adj[v][u]--;
                // Рекурсивно вызываем функцию для следующей вершины
                eulerianUtil(v, adj, path);
            }
        }
        // Добавляем текущую вершину в путь
        path.push_back(u);
    }

    //Метод для вывода эйлерова цикла
    void Graph<int>::printEulerianCycle() 
    {
        // Проверяем наличие эйлерова цикла
        if (!isEulerianCycle()) 
        {
            std::cout << "Graph doesn't contain Eulerian Cycle\n";
            return;
        }

        // Создаем вектор для хранения эйлерова цикла
        std::vector<int> path;
        // Создаем копию матрицы смежности
        std::vector<std::vector<int>> adj = adjacencyMatrix;

        // Вызываем вспомогательную функцию для построения эйлерова цикла
        eulerianUtil(0, adj, path);

        // Переворачиваем путь, чтобы получить правильный порядок вершин
        std::reverse(path.begin(), path.end());

        // Выводим эйлеров цикл
        for (int v : path) 
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}