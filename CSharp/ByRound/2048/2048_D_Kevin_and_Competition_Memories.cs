using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());

        while (testCases-- > 0)
        {
            string[] nm = Console.ReadLine().Split();
            int n = int.Parse(nm[0]);
            int m = int.Parse(nm[1]);

            List<int> a = new List<int>();
            List<int> b = new List<int>();

            // Reading the array a and applying the filtering condition
            string[] aElements = Console.ReadLine().Split();
            foreach (var item in aElements)
            {
                int v = int.Parse(item);
                // Adding values greater than 0 to a
                if (a.Count == 0 || v > a[0])
                {
                    a.Add(v);
                }
            }

            // Reading the array b
            string[] bElements = Console.ReadLine().Split();
            foreach (var item in bElements)
            {
                b.Add(int.Parse(item));
            }

            // Sorting both arrays
            a.Sort();
            b.Sort();

            List<int> rk = new List<int>();

            // Creating rank array based on comparison between arrays a and b
            int j = 0;
            foreach (var bi in b)
            {
                while (j < a.Count && a[j] < bi)
                {
                    j++;
                }
                if (j > 0 && j < a.Count)
                {
                    rk.Add(a.Count - j);
                }
            }

            // Sorting rk in descending order
            rk.Sort((x, y) => y.CompareTo(x));

            // Output results for each i in 1 to m
            for (int i = 1; i <= m; i++)
            {
                int r = m % i;
                long ans = m / i;

                // Accumulate ranks based on the index step
                for (int j2 = r; j2 < rk.Count; j2 += i)
                {
                    ans += rk[j2];
                }

                Console.Write(ans + " ");
            }
            Console.WriteLine();
        }
    }
}
