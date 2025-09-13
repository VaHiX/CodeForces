using System;
using System.Collections.Generic;
using System.Linq;

public class Program
{
    static long GCD(long a, long b)
    {
        while (b != 0)
        {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine());
            long[] p = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
            long[] s = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
            
            long g = p[n - 1];
            bool ok = true;
            
            if (s[0] != g) ok = false;
            
            for (int i = 1; i < n && ok; i++)
                if (p[i - 1] % p[i] != 0) ok = false;
            
            for (int i = 0; i < n - 1 && ok; i++)
                if (s[i + 1] % s[i] != 0) ok = false;
            
            for (int i = 0; i < n && ok; i++)
                if (GCD(p[i], s[i]) != g) ok = false;
            
            for (int i = 0; i < n - 1 && ok; i++)
                if (GCD(p[i], s[i + 1]) != g) ok = false;
            
            Console.WriteLine(ok ? "YES" : "NO");
        }
    }
}