using System;
using System.Collections.Generic;

public class ConnectivityTransformer
{
    private List<int>[] graphF;
    private List<int>[] graphG;
    private bool[] visitedF;
    private bool[] visitedG;
    private int[] componentIdG;
    private HashSet<(int, int)> blockedEdges;
    private int nodeCount;

    /// <summary>
    /// Computes the minimum number of operations needed to transform graph F to match graph G's connectivity structure.
    /// </summary>
    /// <param name="n">Number of nodes in the graphs.</param>
    /// <param name="edgesF">Edges in graph F (1-indexed pairs).</param>
    /// <param name="edgesG">Edges in graph G (1-indexed pairs).</param>
    /// <returns>Minimum number of operations required.</returns>
    public int MinOperations(int n, int[][] edgesF, int[][] edgesG)
    {
        nodeCount = n;
        graphF = new List<int>[n];
        graphG = new List<int>[n];
        visitedF = new bool[n];
        visitedG = new bool[n];
        componentIdG = new int[n];
        blockedEdges = new HashSet<(int, int)>();

        // Initialize adjacency lists
        for (int i = 0; i < n; i++)
        {
            graphF[i] = new List<int>();
            graphG[i] = new List<int>();
        }

        // Build Graph F
        foreach (var edge in edgesF)
        {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            graphF[u].Add(v);
            graphF[v].Add(u);
        }

        // Build Graph G
        foreach (var edge in edgesG)
        {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            graphG[u].Add(v);
            graphG[v].Add(u);
        }

        // Step 1: Identify connected components in G
        int componentCountG = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visitedG[i])
            {
                componentCountG++;
                DFS_G(i, componentCountG);
            }
        }

        // Step 2: Mark "bridge" edges in F that connect different G components
        int bridgeCount = 0;
        for (int u = 0; u < n; u++)
        {
            foreach (int v in graphF[u])
            {
                if (componentIdG[u] != componentIdG[v])
                {
                    var edge = NormalizeEdge(u, v);
                    if (!blockedEdges.Contains(edge))
                    {
                        blockedEdges.Add(edge);
                        bridgeCount++;
                    }
                }
            }
        }

        // Step 3: Count components in F after removing blocked edges
        int componentCountF = 0;
        for (int i = 0; i < n; i++)
        {
            if (!visitedF[i])
            {
                componentCountF++;
                DFS_F(i);
            }
        }

        // Result: number of bridge removals + number of connections needed to merge extra components
        return bridgeCount + (componentCountF - componentCountG);
    }

    // DFS for graph G, assigning component ID
    private void DFS_G(int u, int componentId)
    {
        visitedG[u] = true;
        componentIdG[u] = componentId;

        foreach (int v in graphG[u])
        {
            if (!visitedG[v])
                DFS_G(v, componentId);
        }
    }

    // DFS for graph F, ignoring blocked edges
    private void DFS_F(int u)
    {
        visitedF[u] = true;

        foreach (int v in graphF[u])
        {
            var edge = NormalizeEdge(u, v);
            if (!visitedF[v] && !blockedEdges.Contains(edge))
            {
                DFS_F(v);
            }
        }
    }

    // Normalize an edge so (u,v) and (v,u) are treated the same
    private (int, int) NormalizeEdge(int u, int v)
    {
        return u < v ? (u, v) : (v, u);
    }
}

class Solution
{
    static void Main()
    {
        var solver = new ConnectivityTransformer();
        
        // Read number of test cases
        int t = int.Parse(Console.ReadLine());

        List<int> res = new List<int>();
        
        while (t-- > 0)
        {
            // Read n, m1, m2
            string[] header = Console.ReadLine()
                                     .Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int n  = int.Parse(header[0]);
            int m1 = int.Parse(header[1]);
            int m2 = int.Parse(header[2]);
            
            // Read edges of F
            int[][] edgesF = new int[m1][];
            for (int i = 0; i < m1; i++)
            {
                string[] parts = Console.ReadLine()
                                        .Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                edgesF[i] = new[] { int.Parse(parts[0]), int.Parse(parts[1]) };
            }
            
            // Read edges of G
            int[][] edgesG = new int[m2][];
            for (int i = 0; i < m2; i++)
            {
                string[] parts = Console.ReadLine()
                                        .Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                edgesG[i] = new[] { int.Parse(parts[0]), int.Parse(parts[1]) };
            }
            
            // Compute and print result
            int result = solver.MinOperations(n, edgesF, edgesG);
            // Console.WriteLine(result);
            res.Add(result);
        }
        foreach(var i in res) {
            Console.WriteLine(i);
        }
    }
}
