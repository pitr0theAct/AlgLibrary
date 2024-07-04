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
    Graph<T>::Graph(int vertices) : vertices(vertices) //�����������
    {
        adjacencyMatrix.resize(vertices, std::vector<T>(vertices, 0));
    }

    Graph<int>::Graph(const std::vector<std::vector<int>>& adjacencyMatrix)
        : vertices(adjacencyMatrix.size()), adjacencyMatrix(adjacencyMatrix) {}

    //����� ��� ���������� �����
    void Graph<int>::addEdge(int v, int w, int weight) 
    {
        // ��������� ����� ����� ��������� v � w � ����� weight
        adjacencyMatrix[v][w] = weight;
        adjacencyMatrix[w][v] = weight; // ��� ������������������ �����
    }

    //����� ��� ���������� ������ � ������ 
    std::vector<int> Graph<int>::bfs(int start) 
    {
        // ���������� ��������� ������ � ������ (BFS)
        std::vector<bool> visited(vertices, false); // ������ ��� ������������ ���������� ������
        std::vector<int> result; // ������ ��� �������� ���������� ������
        std::queue<int> q; // ������� ��� ������ ������

        visited[start] = true; // �������� ��������� ������� ��� ����������
        q.push(start); // ��������� ��������� ������� � �������

        while (!q.empty()) 
        {
            int v = q.front(); // ��������� ������� �� �������
            q.pop();
            result.push_back(v); // ��������� ������� � ��������� ������

            // �������� �� ���� ������� ��������
            for (int i = 0; i < vertices; ++i) 
            {
                // ���� ���� ����� ����� ������� �������� � ��������, � �������� ������� �� ��������
                if (adjacencyMatrix[v][i] != 0 && !visited[i]) 
                {
                    visited[i] = true; // �������� �������� ������� ��� ����������
                    q.push(i); // ��������� �������� ������� � �������
                }
            }
        }

        return result;
    }


    //����� ��� ���������� ������ � �������
    std::vector<int> Graph<int>::dfs(int start) 
    {
        // ���������� ��������� ������ � ������� (DFS)
        std::vector<bool> visited(vertices, false); // ������ ��� ������������ ���������� ������
        std::vector<int> result; // ������ ��� �������� ���������� ������
        std::stack<int> s; // ���� ��� ������ ������
        s.push(start); // ��������� ��������� ������� � ����

        while (!s.empty()) // ���� ������� �� �����
        {
            int v = s.top(); // ��������� ������� �� �����
            s.pop();

            if (!visited[v]) 
            {
                visited[v] = true; // �������� ������� ��� ����������
                result.push_back(v); // ��������� ������� � ��������� ������

                // �������� �� ���� ������� �������� � �������� �������
                for (int i = vertices - 1; i >= 0; --i) 
                {
                    // ���� ���� ����� ����� ������� �������� � ��������, � �������� ������� �� ��������
                    if (adjacencyMatrix[v][i] != 0 && !visited[i]) 
                    {
                        s.push(i); // ��������� �������� ������� � ����
                    }
                }
            }
        }

        return result;
    }


    // ����� ��� ���������� ����������� ���� ������� ��������
    std::vector<int> Graph<int>::dijkstra(int src) 
    {
        // ���������� ��������� �������� ��� ������ ���������� ����� �� �������� �������
        std::vector<int> dist(vertices, std::numeric_limits<int>::max()); // ������ ��� �������� ���������� �� ������
        std::vector<bool> visited(vertices, false); // ������ ��� ������������ ���������� ������
        dist[src] = 0; // ���������� �� �������� ������� ����� 0

        for (int i = 0; i < vertices; ++i) 
        {
            int u = -1;
            // ������� ������� � ����������� ����������� ����� ������������ ������
            for (int j = 0; j < vertices; ++j)
            {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                {
                    u = j;
                }
            }

            // ���� ���������� �� ������� u ����� �������������, �� ������� �� �����
            if (dist[u] == std::numeric_limits<int>::max()) break;

            visited[u] = true; // �������� ������� u ��� ����������

            // ��������� ���������� �� �������� ������
            for (int v = 0; v < vertices; ++v) 
            {
                // ���� ���� ����� ����� ��������� u � v, � v �� ��������,
                // � ���������� �� v ����� u ������ �������� ���������� �� v
                if (adjacencyMatrix[u][v] && !visited[v] && dist[u] + adjacencyMatrix[u][v] < dist[v]) 
                {
                    dist[v] = dist[u] + adjacencyMatrix[u][v]; // ��������� ���������� �� v
                }
            }
        }

        return dist; // ���������� ������ ���������� �� ������
    }


    // �������� ��������-����� ��� ������ ���������� �����
    std::vector<int> Graph<int>::bellmanFord(int src) 
    {
        // ������� ������ dist ��� �������� ���������� �� ������
        // �������������� ��� ���������� ������������ ��������� ���� T
        std::vector<int> dist(vertices, std::numeric_limits<int>::max());

        // ������������� ���������� �� �������� ������� ������ 0
        dist[src] = 0;

        // ��������� (vertices - 1) �������� ��������� ��������-�����
        for (int i = 1; i < vertices; ++i) 
        {
            // ���������� �� ���� ������ �����
            for (int u = 0; u < vertices; ++u) 
            {
                for (int v = 0; v < vertices; ++v) 
                {
                    // ���� ���������� ����� ����� ��������� u � v
                    // � ���������� �� ������� u �� ����������
                    // � ����� ���������� �� ������� v ������ ��������
                    if (adjacencyMatrix[u][v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjacencyMatrix[u][v] < dist[v]) 
                    {
                        // ��������� ���������� �� ������� v
                        dist[v] = dist[u] + adjacencyMatrix[u][v];
                    }
                }
            }
        }

        // ��������� ������� ������������� ������
        for (int u = 0; u < vertices; ++u) 
        {
            for (int v = 0; v < vertices; ++v) 
            {
                // ���� ���������� ����� ����� ��������� u � v
                // � ���������� �� ������� u �� ����������
                // � ����� ���������� �� ������� v ������ ��������
                if (adjacencyMatrix[u][v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjacencyMatrix[u][v] < dist[v]) 
                {
                    // ���� �������� ������������� ����
                    std::cerr << "Graph contains a negative-weight cycle" << std::endl;
                    // ���������� ������ ������, ����������� �� ������
                    return {};
                }
            }
        }

        // ���������� ������ ���������� ���������� �� �������� ������� �� ���� ��������� ������
        return dist;
    }


    //��������� �������
    struct Edge 
    {
        int src, dest;
        int weight;
        bool operator<(const Edge& other) const 
        {
            return weight < other.weight;
        }
    };

    // ����� ��� ���������� ����� ������
    int Graph<int>::find(std::vector<int>& parent, int i) 
    {
        // ���� �������� ������� i �� ����� ����� ������� i
        if (parent[i] != i) 
        {
            // ���������� ������� �������� ������� ��� ������� i � ��������� �������� ������� i
            parent[i] = find(parent, parent[i]);
        }
        // ���������� �������� (�������� �������) ��� ������� i
        return parent[i];
    }

    void Graph<int>::unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y) 
    {
        // ������� �������� ������� ��� ������ x � y
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        // ���� ���� �������� ������� rootX ������ ����� �������� ������� rootY
        if (rank[rootX] < rank[rootY]) 
        {
            // ������������� rootY � �������� �������� ��� rootX
            parent[rootX] = rootY;
        }
        // ���� ���� �������� ������� rootX ������ ����� �������� ������� rootY
        else if (rank[rootX] > rank[rootY]) 
        {
            // ������������� rootX � �������� �������� ��� rootY
            parent[rootY] = rootX;
        }
        // ���� ����� �������� ������ �����
        else 
        {
            // ������������� rootX � �������� �������� ��� rootY
            parent[rootY] = rootX;
            // ����������� ���� �������� ������� rootX �� 1
            rank[rootX]++;
        }
    }


    // ����� ��� ���������� ������������ ��������� ������ (�������� ��������)
    std::pair<int, std::vector<std::pair<int, int>>> Graph<int>::kruskal() 
    {
        // ������� ������ ����� �����
        std::vector<Edge> edges;
        // �������� �� ���� ����� ������ � ������� ���������
        for (int u = 0; u < vertices; ++u) 
        {
            for (int v = u + 1; v < vertices; ++v) 
            {
                // ���� ����� ��������� u � v ���� �����
                if (adjacencyMatrix[u][v]) 
                {
                    // ��������� ����� � ������ �����
                    edges.push_back({ u, v, adjacencyMatrix[u][v] });
                }
            }
        }

        // ��������� ������ ����� �� ����������� ����
        std::sort(edges.begin(), edges.end());

        // ������� ������ ��� �������� ��������� ������
        std::vector<int> parent(vertices);
        // ������� ������ ��� �������� ������ ������, �������������� ��� ����� ������
        std::vector<int> rank(vertices, 0);
        // �������������� ������ ������� ��� ���� ����������� ������������ �������
        for (int i = 0; i < vertices; ++i) 
        {
            parent[i] = i;
        }

        // ���������� ��� �������� ���� ������������ ��������� ������
        int mstWeight = 0;
        // ������ ��� �������� ����� ������������ ��������� ������
        std::vector<std::pair<int, int>> mstEdges;
        // �������� �� ���� ������ � ��������������� ������� �����
        for (const auto& edge : edges) 
        {
            // ������� �������� ������� ��� ������ �������� �����
            int rootX = find(parent, edge.src);
            int rootY = find(parent, edge.dest);

            // ���� �������� ������� �������� (����� �� �������� ����)
            if (rootX != rootY) 
            {
                // ��������� ��� �������� ����� � ������ ���� ������������ ��������� ������
                mstWeight += edge.weight;
                // ���������� ���������, ���������� ����� �������� �����
                unionSets(parent, rank, rootX, rootY);
                // ��������� ������� ����� � ������ ����� ������������ ��������� ������
                mstEdges.push_back({ edge.src, edge.dest });
            }
        }

        // ���������� ����: ��� ������������ ��������� ������ � ������ ����� ������������ ��������� ������
        return { mstWeight, mstEdges };
    }


    // ����� ������� ��������� �������� �� ���� ���������
    bool Graph<int>::isEulerianCycle() 
    {
        // ���������, �������� �� ���� �������
        if (!isConnected()) 
        {
            return false;
        }

        // ������������ ���������� ������ � �������� ��������
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

        // ���� ���������� ������ � �������� �������� ����� 0, ���� �������� ���������
        return oddDegreeCount == 0;
    }

    template<typename T>
    bool Graph<T>::isConnected() //����� ������� ��������� �������� �� ���� �������
    {
        // ������� ������ ��� ������������ ���������� ������
        std::vector<bool> visited(vertices, false);
        // ������� ������� ��� ������ � ������
        std::queue<int> q;

        // ���� ������ ������� � ��������� ��������
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

        // ���� ��� ������� ����� ������� �������, ���� ��������� �������
        if (i == vertices) 
        {
            return true;
        }

        // �������� ����� � ������ � ��������� �������
        q.push(i);
        visited[i] = true;

        // ��������� ����� � ������
        while (!q.empty()) 
        {
            int v = q.front();
            q.pop();

            // ������������ �������� �������
            for (int j = 0; j < vertices; ++j) 
            {
                if (adjacencyMatrix[v][j] && !visited[j]) 
                {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }

        // ���������, ��� �� ������� � ��������� �������� ���� ��������
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

        // ���� ��� ������� � ��������� �������� ���� ��������, ���� �������
        return true;
    }


    bool Graph<int>::hasEulerianCycle() 
    {
        // �������� ������� isEulerianCycle ��� �������� ������� �������� �����
        return isEulerianCycle();
    }

    
    void Graph<int>::eulerianUtil(int u, std::vector<std::vector<int>>& adj, std::vector<int>& path) 
    {
        // ������������ ��� �������� �������
        for (int v = 0; v < vertices; ++v)
        {
            if (adj[u][v]) 
            {
                // ������� ����� ����� ��������� u � v
                adj[u][v]--;
                adj[v][u]--;
                // ���������� �������� ������� ��� ��������� �������
                eulerianUtil(v, adj, path);
            }
        }
        // ��������� ������� ������� � ����
        path.push_back(u);
    }

    //����� ��� ������ �������� �����
    void Graph<int>::printEulerianCycle() 
    {
        // ��������� ������� �������� �����
        if (!isEulerianCycle()) 
        {
            std::cout << "Graph doesn't contain Eulerian Cycle\n";
            return;
        }

        // ������� ������ ��� �������� �������� �����
        std::vector<int> path;
        // ������� ����� ������� ���������
        std::vector<std::vector<int>> adj = adjacencyMatrix;

        // �������� ��������������� ������� ��� ���������� �������� �����
        eulerianUtil(0, adj, path);

        // �������������� ����, ����� �������� ���������� ������� ������
        std::reverse(path.begin(), path.end());

        // ������� ������� ����
        for (int v : path) 
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}