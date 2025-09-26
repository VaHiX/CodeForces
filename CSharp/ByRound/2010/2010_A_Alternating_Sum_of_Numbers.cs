using System;
using System.Linq;

namespace mainc_
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string input = Console.ReadLine();

            int n = int.Parse(input);

            while (n-- > 0)
            {
                solve();
            }

            void solve()
            {
                string input = Console.ReadLine();
                int n = int.Parse(input);
                input = Console.ReadLine();
                int[] num = input.Split(' ').Select(int.Parse).ToArray();

                int ans = 0;
                for (int i = 0; i < n; i++)
                {
                    if (i % 2 == 0)
                    {
                        ans += num[i];
                    }
                    else
                    {
                        ans -= num[i];
                    }
                }

                Console.WriteLine(ans);
            }
        }
    }
}
