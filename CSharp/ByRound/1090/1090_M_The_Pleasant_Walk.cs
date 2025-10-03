using System;
using System.Collections.Generic;
using System.Linq;
using System.Globalization;
using System.Threading;

namespace M
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;
            int tc = 1;
            //tc = int.Parse(Console.ReadLine());
            while (tc-- > 0)
            {
                solve();
            }
        }

        // write your code in solve function
        static void solve()
        {
            int[] arr = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
            int n = arr[0];
            int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

            int cur = 1;
            int maximal = 1;
            for (int i=1; i<n; i++) {
                if (a[i] != a[i-1]) {
                    cur++;
                } else {
                    cur = 1;
                }
                maximal = Math.Max(cur, maximal);
            }

            Console.WriteLine(maximal);
        }
    }
}