using System;
using System.Collections.Generic;
using System.Linq;
 
class PerfectPermutation
{
    static void DFS(int node, int parent, List<List<int>> tree, int[] dist)
    {
        foreach (int neighbor in tree[node])
        {
            if (neighbor != parent)
            {
                dist[neighbor] = dist[node] + 1;
                DFS(neighbor, node, tree, dist);
            }
        }
    }
 
    static void Solve()
    {
        string[] inputs = Console.ReadLine().Split();
        int n = int.Parse(inputs[0]);
        int st = int.Parse(inputs[1]);
        int en = int.Parse(inputs[2]);
        
        List<List<int>> tree = new List<List<int>>(new List<int>[n + 1]);
        for (int i = 0; i <= n; i++) tree[i] = new List<int>();
        
        for (int i = 0; i < n - 1; i++)
        {
            inputs = Console.ReadLine().Split();
            int u = int.Parse(inputs[0]);
            int v = int.Parse(inputs[1]);
            tree[u].Add(v);
            tree[v].Add(u);
        }
        
        int[] dist = Enumerable.Repeat(-1, n + 1).ToArray();
        dist[en] = 0;
        DFS(en, -1, tree, dist);
        
        List<int> perm = Enumerable.Range(1, n).ToList();
        perm.Sort((a, b) => dist[b].CompareTo(dist[a]));
        
        if (dist[st] == -1)
        {
            Console.WriteLine("-1");
        }
        else
        {
            Console.WriteLine(string.Join(" ", perm));
        }
    }
 
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0) Solve();
    }
}