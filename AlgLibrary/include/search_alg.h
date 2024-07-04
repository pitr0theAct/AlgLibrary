#pragma once
#include <vector>

namespace Search 
{
    class Search 
    {
    public:
        static int linearSearch(const std::vector<int>& arr, int key);
        static int binarySearch(const std::vector<int>& arr, int key, int left, int right);
        static int jumpSearch(const std::vector<int>& arr, int key);
    };

} 
 