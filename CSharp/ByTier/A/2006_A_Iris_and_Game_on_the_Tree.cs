using System;
using System.Collections.Generic;

class Program
{
    const int N = 114514;
    static int[] d = new int[N];

    static void Main(string[] args)
    {
        int T = int.Parse(Console.ReadLine());
        while (T-- > 0)
        {
            // Reading the number of nodes
            int n = int.Parse(Console.ReadLine());

            // Reset degree array
            for (int i = 1; i <= n; i++)
                d[i] = 0;

            // Reading edges and computing degree of nodes
            for (int i = 1; i < n; i++)
            {
                string[] edge = Console.ReadLine().Split();
                int u = int.Parse(edge[0]);
                int v = int.Parse(edge[1]);
                d[u]++;
                d[v]++;
            }

            // Reading the binary string (from node 1)
            string s = Console.ReadLine();

            // Counters for '0', '1', and '?' characters
            int[] c = new int[3]; // c[0] for '0', c[1] for '1', c[2] for '?'
            int a2 = 0;

            // Count '?' in nodes 2 to n
            for (int i = 2; i <= n; i++)
            {
                if (s[i - 1] == '?')
                    a2++;
            }

            // Count based on leaf nodes (degree 1)
            for (int i = 2; i <= n; i++)
            {
                if (d[i] == 1)
                {
                    if (s[i - 1] == '?')
                        c[2]++;
                    else
                        c[s[i - 1] - '0']++;
                }
            }

            // Output based on the value of the first node (s[0])
            if (s[0] != '?')
            {
                Console.WriteLine(c[(s[0] - '0') ^ 1] + (c[2] + 1) / 2);
            }
            else if (c[0] != c[1])
            {
                Console.WriteLine(Math.Max(c[0], c[1]) + c[2] / 2);
            }
            else
            {
                Console.WriteLine(c[0] + (c[2] + (a2 - c[2]) % 2) / 2);
            }
        }
    }
}
