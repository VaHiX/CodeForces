using System;
using System.Collections.Generic;

class Solution
{
    // Function to compute mex of a list of integers
    static int ComputeMex(List<int> list)
    {
        HashSet<int> set = new HashSet<int>(list);
        int mex = 0;
        while (set.Contains(mex)) mex++;
        return mex;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            string[] inputs = Console.ReadLine().Split();
            int n = int.Parse(inputs[0]);
            int x = int.Parse(inputs[1]);
            int y = int.Parse(inputs[2]);

            // Build adjacency list
            List<int>[] adj = new List<int>[n + 1];
            for (int i = 1; i <= n; i++)
            {
                adj[i] = new List<int>();
                adj[i].Add(i == 1 ? n : i - 1);
                adj[i].Add(i == n ? 1 : i + 1);
            }

            // Add chord
            adj[x].Add(y);
            adj[y].Add(x);

            // Initialize labels
            int[] labels = new int[n + 1];
            for (int i = 1; i <= n; i++) labels[i] = -1;

            // Assign labels
            labels[x] = 0;
            labels[y] = 1;

            // Initialize queue
            Queue<int> queue = new Queue<int>();
            queue.Enqueue(x);
            queue.Enqueue(y);

            // Perform BFS to assign labels
            while (queue.Count > 0)
            {
                int u = queue.Dequeue();
                foreach (int v in adj[u])
                {
                    if (labels[v] == -1)
                    {
                        // Collect labels of neighbors
                        List<int> neighborLabels = new List<int>();
                        foreach (int neighbor in adj[v])
                        {
                            if (labels[neighbor] != -1)
                            {
                                neighborLabels.Add(labels[neighbor]);
                            }
                        }

                        // Compute mex
                        int mex = ComputeMex(neighborLabels);
                        labels[v] = mex;
                        queue.Enqueue(v);
                    }
                }
            }

            // Assign 0 to any remaining nodes
            for (int i = 1; i <= n; i++)
            {
                if (labels[i] == -1)
                    labels[i] = 0;
            }

            // Output result
            for (int i = 1; i <= n; i++)
            {
                Console.Write(labels[i]);
                if (i < n) Console.Write(" ");
                else Console.WriteLine();
            }
        }
    }
}
