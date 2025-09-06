using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        // Read the number of test cases
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            // Read the number of nodes
            int n = int.Parse(Console.ReadLine());
            var adj = new List<int>[n];
            for (int i = 0; i < n; i++)
                adj[i] = new List<int>();

            // Read the edges
            for (int i = 1; i < n; i++)
            {
                var edge = Console.ReadLine().Split().Select(int.Parse).ToArray();
                int u = edge[0] - 1;
                int v = edge[1] - 1;
                adj[u].Add(v);
                adj[v].Add(u);
            }

            var d = new long[n];
            var s = new long[n];
            var dc = new long[n];
            var dcs = new long[n];

            // Depth-First Search to calculate depths and subtree sizes
            void Dfs1(int v, int p = -1)
            {
                dc[d[v]]++;
                long sz = 1;
                foreach (int w in adj[v])
                {
                    if (w != p)
                    {
                        d[w] = d[v] + 1;
                        Dfs1(w, v);
                        sz += s[w];
                    }
                }
                s[v] = sz;
            }

            Dfs1(0);

            // Calculate dcs array
            Array.Copy(dc, dcs, n);
            for (int i = n - 2; i >= 0; i--)
                dcs[i] += dcs[i + 1];

            long ans = 0, ans2 = 0;

            // Depth-First Search to calculate answers
            void Dfs2(int v, int p = -1)
            {
                // v is min
                ans += 2 * d[v] * (dcs[d[v]] - s[v]);
                // v is lca
                long subcnt = s[v] - 1, lcnt = 0;
                foreach (int w in adj[v])
                {
                    if (w != p)
                    {
                        lcnt += (subcnt - s[w]) * s[w];
                        Dfs2(w, v);
                    }
                }
                ans2 += (2 * d[v] + 1) * (lcnt / 2);
            }

            Dfs2(0);

            for (int i = 0; i < n; i++)
            {
                ans2 += i * dc[i] * (dc[i] - 1);
            }

            Console.WriteLine(ans - ans2);
        }
    }
}
