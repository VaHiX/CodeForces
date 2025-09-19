using System;

namespace Solving
{
    public class Program
    {
        static void Main(string[] args)
        {
            int T = Convert.ToInt32(Console.ReadLine());
            while (T-- > 0)
            {
                Solve();
            }
        }

        static void Solve()
        {
            string[] input = Console.ReadLine().Split(' ');
            int n = Convert.ToInt32(input[0]);
            int k = Convert.ToInt32(input[1]);

            int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

            Array.Sort(a);
            Array.Reverse(a);

            for (int i = 1; i < n; i += 2)
            {
                int curr = Math.Min(k, a[i - 1] - a[i]);
                k -= curr;
                a[i] += curr;
                if (k == 0) break;
            }

            int ans = 0;
            for (int i = 0; i < n; i++)
            {
                ans += a[i] * (i % 2 == 0 ? 1 : -1);
            }

            Console.WriteLine(ans);
        }
    }
}
