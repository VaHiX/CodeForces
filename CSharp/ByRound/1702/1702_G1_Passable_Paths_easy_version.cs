// Problem: CF 1702 G1 - Passable Paths (easy version)
// https://codeforces.com/contest/1702/problem/G1

﻿/*
 * Problem: Determine if a set of vertices in a tree forms a passable path.
 *
 * Approach:
 * - Build the tree from input edges.
 * - Perform BFS from root node to compute depths and parent relationships.
 * - For each query:
 *   - Sort vertices by depth in descending order.
 *   - Process vertices from highest to lowest depth.
 *   - Keep track of current path vertices (cur).
 *   - For each vertex, move up the tree until reaching the same depth as the next vertex.
 *   - Check if the path can be formed without contradictions.
 *
 * Time Complexity: O(n + q * k * log k) where n is number of nodes, q is number of queries, k is average size of a query set.
 * Space Complexity: O(n + k) for storing the tree and processing query data.
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
            int count = 1;
            List<string> output = new List<string>();
            for (int z = 0; z < count; z++)
            {
                var n = int.Parse(Console.ReadLine()); // Read number of nodes
                bool can = true;
                List<int>[] nodes = new List<int>[n]; // Adjacency list for the tree
                for (int i = 0; i < n; i++)
                {
                    nodes[i] = new List<int>(); // Initialize adjacency list
                }
                for (int i = 0; i < n - 1; i++)
                {
                    var a = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList(); // Read edge
                    nodes[a[0] - 1].Add(a[1] - 1); // Add connection in both directions
                    nodes[a[1] - 1].Add(a[0] - 1);
                }
                int[] depth = new int[n]; // Store depth of each node
                int[] parents = new int[n]; // Store parent of each node
                for (int i = 0; i < n; i++)
                    depth[i] = -1; // Initialize depths to -1 (unvisited)
                depth[0] = 0; // Root node has depth 0
                Queue<int> p = new Queue<int>(); // BFS queue
                p.Enqueue(0);
                while (p.Count > 0)
                {
                    int i = p.Dequeue(); // Get current node
                    nodes[i]
                        .ForEach(j =>
                        { // Visit all neighbors
                            if (depth[j] == -1)
                            { // If neighbor is not visited
                                depth[j] = depth[i] + 1; // Set depth
                                parents[j] = i; // Set parent
                                p.Enqueue(j); // Add neighbor to queue
                            }
                        });
                }
                int q = int.Parse(Console.ReadLine()); // Read number of queries
                for (int w = 0; w < q; w++)
                {
                    can = true;
                    int m = int.Parse(Console.ReadLine()); // Read size of query set
                    var a = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList(); // Read vertices in query set
                    List<int[]> d = new List<int[]>(); // Store vertices with their depths
                    for (int i = 0; i < m; i++)
                    {
                        int[] te = new int[2];
                        te[0] = a[i] - 1; // Convert to 0-indexed
                        te[1] = depth[a[i] - 1]; // Get depth
                        d.Add(te);
                    }
                    d = d.OrderBy(i => -i[1]).ToList(); // Sort by depth descending
                    List<int[]> cur = new List<int[]>(); // Current path tracking
                    cur.Add(d[0]); // Add the highest depth node initially
                    bool merged = false; // Flag for path convergence
                    for (int i = 1; i < m; i++)
                    {
                        while (cur.Select(j => j[1]).Max() > d[i][1])
                        { // While current path is higher than target depth
                            if (merged)
                            { // If already merged and not possible to proceed
                                can = false;
                                break;
                            }
                            for (int k = 0; k < cur.Count; k++)
                            {
                                cur[k][0] = parents[cur[k][0]]; // Move up one level
                                cur[k][1] = depth[cur[k][0]]; // Update depth
                            }
                            if (cur.Count > 1 && cur[0][0] == cur[1][0])
                            { // If two vertices meet at same parent
                                merged = true;
                            }
                        }
                        if (cur.Count > 1 && cur[0][0] == cur[1][0])
                        { // After movement, check again
                            if (i != m - 1 || cur[0][0] != d[m - 1][0])
                            { // If path can't continue or mismatch
                                can = false;
                                break;
                            }
                        }
                        if (!cur.Select(j => j[0]).ToList().Contains(d[i][0]))
                        { // If new node not in current path
                            cur.Add(d[i]); // Add it
                            if (cur.Count > 2)
                            { // If more than two nodes in path
                                can = false; // Not a valid passable path
                                break;
                            }
                        }
                    }
                    if (can)
                        output.Add("YES"); // Valid path
                    else
                        output.Add("NO"); // Invalid path
                }
            }
            output.ForEach(d => Console.WriteLine(d)); // Output results
        }
    }
}


// https://github.com/VaHiX/CodeForces/
