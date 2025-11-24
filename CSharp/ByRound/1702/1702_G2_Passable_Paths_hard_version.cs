// Problem: CF 1702 G2 - Passable Paths (hard version)
// https://codeforces.com/contest/1702/problem/G2

/*
 * Problem: G2. Passable Paths (hard version)
 *
 * Algorithm/Techniques:
 * - Tree processing with binary lifting for LCA (Lowest Common Ancestor)
 * - For each query, we determine if a set of vertices forms a passable path
 * - A set is passable if we can construct a simple path in the tree that visits all vertices from the set
 * - We use binary lifting to efficiently compute ancestors and LCA
 * - We track the depth and parent of each node, then build a skipParents table for binary lifting
 * - For each query:
 *   - Sort the vertices by depth (descending)
 *   - Process vertices one by one, maintaining a list of current "active" nodes
 *   - Use binary lifting to move nodes up to the same depth
 *   - Check if we can merge nodes correctly to form a path
 *
 * Time Complexity: O(n log n + q * k * log n) where n is number of nodes, q is number of queries, k is average set size
 * Space Complexity: O(n * log n) for the skipParents table and auxiliary data structures
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace VaHiX
{
    partial class MainClass
    {
        public static void Main(string[] args)
        {
            try
            {
                int count = 1;
                List<string> output = new List<string>();
                for (int z = 0; z < count; z++)
                {
                    var n = int.Parse(Console.ReadLine());
                    bool can = true;
                    List<int>[] nodes = new List<int>[n];
                    for (int i = 0; i < n; i++)
                    {
                        nodes[i] = new List<int>();
                    }
                    for (int i = 0; i < n - 1; i++)
                    {
                        var a = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
                        nodes[a[0] - 1].Add(a[1] - 1);
                        nodes[a[1] - 1].Add(a[0] - 1);
                    }
                    int[] depth = new int[n];
                    int[] parents = new int[n];
                    for (int i = 0; i < n; i++)
                        depth[i] = -1;
                    depth[0] = 0;
                    Queue<int> p = new Queue<int>();
                    p.Enqueue(0);
                    int[,] skipParents = new int[n, 220]; // Binary lifting table
                    parents[0] = -1;
                    skipParents[0, 0] = -1;
                    while (p.Count > 0)
                    {
                        int i = p.Dequeue();
                        nodes[i]
                            .ForEach(j =>
                            {
                                if (depth[j] == -1)
                                {
                                    depth[j] = depth[i] + 1;
                                    parents[j] = i;
                                    skipParents[j, 0] = i;
                                    p.Enqueue(j);
                                }
                            });
                    }
                    // Build binary lifting table
                    for (int i = 1; i < n; i++)
                    {
                        for (int j = 1; j < 220; j++)
                        {
                            int u = skipParents[i, j - 1];
                            if (u < 0 || u >= n)
                                break;
                            skipParents[i, j] = parents[u];
                            if (skipParents[i, j] < 0)
                                break;
                        }
                    }
                    int q = int.Parse(Console.ReadLine());
                    for (int w = 0; w < q; w++)
                    {
                        can = true;
                        int m = int.Parse(Console.ReadLine());
                        var a = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList();
                        List<int[]> d = new List<int[]>();
                        for (int i = 0; i < m; i++)
                        {
                            int[] te = new int[2];
                            te[0] = a[i] - 1; // vertex index
                            te[1] = depth[a[i] - 1]; // depth
                            d.Add(te);
                        }
                        // Sort by depth (descending)
                        d = d.OrderBy(i => -i[1]).ToList();
                        List<int[]> cur = new List<int[]>();
                        cur.Add(d[0]);
                        bool merged = false;
                        for (int i = 1; i < m; i++)
                        {
                            // Move nodes up the tree until their depths align
                            while (cur.Select(j => j[1]).Max() > d[i][1] + 1)
                            {
                                for (int k = 0; k < cur.Count; k++)
                                {
                                    if (cur[k][1] - d[i][1] >= 2)
                                    {
                                        // Use binary lifting to jump up the tree
                                        cur[k][0] = skipParents[
                                            cur[k][0],
                                            Math.Min(220 - 1, cur[k][1] - d[i][1] - 2)
                                        ];
                                        cur[k][1] = depth[cur[k][0]];
                                    }
                                }
                                // Check if we have merged nodes
                                if (cur.Count > 1 && cur[0][0] == cur[1][0])
                                {
                                    merged = true;
                                }
                            }
                            // If we can't merge anymore and are still at different depths
                            if (cur.Select(j => j[1]).Max() > d[i][1])
                            {
                                if (merged)
                                {
                                    can = false;
                                    break;
                                }
                                // Move nodes up one level
                                for (int k = 0; k < cur.Count; k++)
                                {
                                    cur[k][0] = parents[cur[k][0]];
                                    cur[k][1] = depth[cur[k][0]];
                                }
                            }
                            // Check if nodes have already merged at this point
                            if (cur.Count > 1 && cur[0][0] == cur[1][0])
                            {
                                // If merged but not the final vertex in query, path is invalid
                                if (i != m - 1 || cur[0][0] != d[m - 1][0])
                                {
                                    can = false;
                                    break;
                                }
                            }
                            // Add new vertex to the active list
                            if (!cur.Select(j => j[0]).ToList().Contains(d[i][0]))
                            {
                                cur.Add(d[i]);
                                if (cur.Count > 2)
                                {
                                    can = false;
                                    break;
                                }
                            }
                        }
                        if (can)
                            output.Add("YES");
                        else
                            output.Add("NO");
                    }
                }
                output.ForEach(d => Console.WriteLine(d));
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
        }
    }
}


// https://github.com/VaHiX/CodeForces/
