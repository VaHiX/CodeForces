using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Solve()
    {
        int n, q;
        var input = Console.ReadLine().Split();
        n = int.Parse(input[0]);
        q = int.Parse(input[1]);

        List<List<int>> graph = new List<List<int>>(n);
        for (int i = 0; i < n; i++)
        {
            graph.Add(new List<int>());
        }

        for (int i = 0; i < n - 1; i++)
        {
            input = Console.ReadLine().Split();
            int u = int.Parse(input[0]) - 1;
            int v = int.Parse(input[1]) - 1;
            graph[u].Add(v);
            graph[v].Add(u);
        }

        int[] depth = new int[n];
        int[] d = new int[n];
        int[] parent = new int[n];

        void Dfs(int node, int parentNode)
        {
            if (depth[node] == 1) d[node] = 1;
            if (depth[node] > 1) d[node] = d[parent[parentNode]] + 2 * graph[parentNode].Count;

            parent[node] = parentNode;
            foreach (var neighbor in graph[node])
            {
                if (neighbor == parentNode) continue;
                depth[neighbor] = depth[node] + 1;
                Dfs(neighbor, node);
            }
        }

        Dfs(0, 0);

        while (q-- > 0)
        {
            input = Console.ReadLine().Split();
            int v = int.Parse(input[0]) - 1;
            int p = int.Parse(input[1]);

            int result = d[v];
            List<int> countList = new List<int>();

            while (v != 0 && parent[v] != 0)
            {
                countList.Add(graph[parent[v]].Count);
                v = parent[parent[v]];
            }

            countList.Sort((a, b) => b.CompareTo(a));  // Sort in descending order
            for (int i = 0; i < Math.Min(p, countList.Count); i++)
            {
                result -= 2 * (countList[i] - 1);
            }

            Console.WriteLine(result);
        }
    }

    static void Main(string[] args)
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            Solve();
        }
    }
}
