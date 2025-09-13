using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()!);

        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine()!);
            int[] b = Console.ReadLine()!
                .Split()
                .Select(int.Parse)
                .ToArray();

            // Build position groups for each value
            List<int>[] positions = new List<int>[n + 1];
            for (int i = 0; i <= n; i++) positions[i] = new List<int>();

            for (int i = 0; i < n; i++)
            {
                positions[b[i]].Add(i);
            }

            // Check divisibility condition
            bool valid = true;
            for (int v = 1; v <= n; v++)
            {
                if (positions[v].Count % v != 0)
                {
                    valid = false;
                    break;
                }
            }

            if (!valid)
            {
                Console.WriteLine("-1");
                continue;
            }

            // Reconstruct array 'a'
            int[] a = new int[n];
            int label = 1;

            for (int v = 1; v <= n; v++)
            {
                var posList = positions[v];
                for (int i = 0; i < posList.Count; i += v)
                {
                    for (int j = 0; j < v; j++)
                    {
                        a[posList[i + j]] = label;
                    }
                    label++;
                }
            }

            Console.WriteLine(string.Join(" ", a));
        }
    }
}