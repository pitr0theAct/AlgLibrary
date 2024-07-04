#pragma once
#include <vector>
#include <iostream>

namespace Graph
{
    template<typename T>
    class Graph
    {
    public:
        Graph(int vertices);
        Graph(const std::vector<std::vector<int>>& adjacencyMatrix);
        void addEdge(int v, int w, int weight);
        std::vector<int> bfs(int start);
        std::vector<int> dfs(int start);
        std::vector<int> dijkstra(int src);
        std::vector<int> bellmanFord(int src);
        std::pair<int, std::vector<std::pair<int, int>>> kruskal();
        bool hasEulerianCycle();
        void printEulerianCycle();

    private:
        int vertices;
        std::vector<std::vector<int>> adjacencyMatrix;
        int find(std::vector<int>& parent, int i);
        void unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y);
        bool isSafe(int v, std::vector<int>& path, int pos);
        bool hamCycleUtil(std::vector<int>& path, int pos);
        bool isEulerianCycle();
        bool isConnected();
        void eulerianUtil(int u, std::vector<std::vector<T>>& adj, std::vector<int>& path);
    };
}