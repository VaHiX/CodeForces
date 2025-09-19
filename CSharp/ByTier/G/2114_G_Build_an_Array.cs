using System;
using System.Collections.Generic;

class Program
{
    static int Cal(int a, int b)
    {
        int c = 0,d=0;
        while (b % 2 == 0)
        {
            b /= 2;
            c++;
        }
         while (a % 2 == 0 )
        {
            a /= 2;
            d++;
        }
        return (1 << c) - ((a == b && d<c)? (1<<(d+1))-1 : 0);
    }

    static int Cc(int x)
    {
        int c = 0;
        while (x % 2 == 0)
        {
            x >>= 1;
            c++;
        }
        return 1 << c;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        const string Y = "yes";
        const string N = "no";

        while (t-- > 0)
        {
            var inputs = Console.ReadLine().Split();
            int n = int.Parse(inputs[0]);
            int k = int.Parse(inputs[1]);

            var a = new int[n];
            var suf = new long[n];
            var aInputs = Console.ReadLine().Split();

            for (int i = 0; i < n; i++)
            {
                a[i] = int.Parse(aInputs[i]);
            }

            suf[n - 1] = 0;
            for (int i = n - 2; i >= 0; i--)
            {
                suf[i] = suf[i + 1] + Cal(a[i], a[i + 1]);
                
            }

            long mx = 0, pr = 0;
            for (int i = 0; i < n; i++)
            {
                mx = Math.Max(mx, suf[i] + pr + Cc(a[i]));
                if (i < n - 1)
                    pr += Cal(a[i + 1], a[i]);
            }

            Console.WriteLine(mx>=k?Y:N);
        }
    }
}
