using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace Codeforces
{
    public class Program
    {
        public static int GetInt() => int.Parse(Console.ReadLine());
        public static long GetLong() => long.Parse(Console.ReadLine());

        public static int[] GetIntArray() => Console.ReadLine().Trim().Split(' ').Select(int.Parse).ToArray();
        public static long[] GetLongArray() => Console.ReadLine().Trim().Split(' ').Select(long.Parse).ToArray();
        public static double[] GetDoublesArray() => Console.ReadLine().Trim().Split(' ').Select(d => Convert.ToDouble(d, CultureInfo.InvariantCulture)).ToArray();

        public static string[] GetLines(int n)
        {
            var ans = new string[n];
            for (int i = 0; i < n; i++)
            {
                ans[i] = Console.ReadLine();
            }
            return ans;
        }

        public static long Gcd(long a, long b) => b == 0 ? a : Gcd(b, a % b);

        public static void Solve()
        {
            int n = GetInt();
            int latestStart = int.MinValue;
            int earliestEnd = int.MaxValue;
            for(int i=0; i<n; i++)
            {
                var a = GetIntArray();
                latestStart = Math.Max(latestStart, a[0]);
                earliestEnd = Math.Min(earliestEnd, a[1]);
            }
            int ans = Math.Max(0, latestStart - earliestEnd);

            Console.WriteLine(ans);
        }

        static void Main(string[] args)
        {
            int t = int.Parse(Console.ReadLine());
            for (int i = 0; i < t; i++)
                Solve();
            //Console.Read();
        }
    }
}