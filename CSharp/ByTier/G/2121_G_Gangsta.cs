using System;
using System.Text;

class Program
{
    static long Solve(string s, int n)
    {
        long ans = 0;
        int[] pref = new int[n + 1];

        for (int i = 0; i < n; i++)
        {
            pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : -1);
        }

        for (int i = 1; i <= n; i++)
        {
            ans += (long)i * (n - i + 1);
        }

        Array.Sort(pref);

        for (int i = 0; i <= n; i++)
        {
            ans += (long)pref[i] * (2L * i - n);
        }
        return ans / 2;
    }


    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        for (int ti = 0; ti < t; ti++)
        {
            int n = int.Parse(Console.ReadLine());
            string s = Console.ReadLine();
            Console.WriteLine(Solve(s, n));
        }
    }
}