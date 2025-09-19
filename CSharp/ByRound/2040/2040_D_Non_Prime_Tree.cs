using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());
        
        while (testCases-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            List<List<int>> graph = new List<List<int>>(n);
            for (int i = 0; i < n; i++)
            {
                graph.Add(new List<int>());
            }
            
            for (int i = 0; i < n - 1; i++)
            {
                string[] edge = Console.ReadLine().Split();
                int a = int.Parse(edge[0]) - 1;
                int b = int.Parse(edge[1]) - 1;
                graph[a].Add(b);
                graph[b].Add(a);
            }
            
            List<int> result = new List<int>(new int[n]);
            int lastValue = 1;
            result[0] = lastValue;
            
            // Depth-First Search function
            void Dfs(int node, int parent)
            {
                foreach (int neighbor in graph[node])
                {
                    if (neighbor == parent) continue;
                    result[neighbor] = lastValue + 1;
                    while (result[neighbor] != result[node] + 1 && 
                           (result[neighbor] % 2 != result[node] % 2 || result[neighbor] - result[node] == 2))
                    {
                        result[neighbor]++;
                    }
                    lastValue = result[neighbor];
                    Dfs(neighbor, node);
                }
            }
            
            Dfs(0, -1);
            
            Console.WriteLine(string.Join(" ", result));
        }
    }
}
