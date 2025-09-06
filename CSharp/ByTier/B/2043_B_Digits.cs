using System;
using System.Collections.Generic;

class Program
{
    static List<int> DetermineDigits(long n, long d)
    {
        var ans = new List<int>();

        // Always include 1
        ans.Add(1);

        // Include 3 if n >= 3 or d is divisible by 3
        if (n >= 3 || d % 3 == 0)
        {
            ans.Add(3);
        }

        // Include 5 if d is 5
        if (d == 5)
        {
            ans.Add(5);
        }

        // Include 7 if n >= 3 or (n == 2 and d == 7)
        if (n >= 3 || (n == 2 && d == 7))
        {
            ans.Add(7);
        }

        // Include 9 if special condition or n >= 6
        if (n >= 6)
        {
            ans.Add(9);
        }
        else
        {
            long factorial = 1;
            for (int i = 2; i <= n; i++)
            {
                factorial *= i;
            }
            if ((factorial * d) % 9 == 0)
            {
                ans.Add(9);
            }
        }

        return ans;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());

        while (t-- > 0)
        {
            string[] inputs = Console.ReadLine().Split(' ');
            long n = long.Parse(inputs[0]);
            long d = long.Parse(inputs[1]);

            List<int> ans = DetermineDigits(n, d);

            Console.WriteLine(string.Join(" ", ans));
        }
    }
}
