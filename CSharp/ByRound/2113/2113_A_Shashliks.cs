using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());

        while (t-- > 0)
        {
            string[] input = Console.ReadLine().Split();
            long k = long.Parse(input[0]);
            long a = long.Parse(input[1]);
            long b = long.Parse(input[2]);
            long x = long.Parse(input[3]);
            long y = long.Parse(input[4]);

            long result1 = Cook(k, a, x, b, y);
            long result2 = Cook(k, b, y, a, x);

            Console.WriteLine(Math.Max(result1, result2));
        }
    }

    static long Cook(long temp, long a1, long x1, long a2, long x2)
    {
        long count = 0;

        while (temp >= a1)
        {
            long cnt = (temp - a1) / x1 + 1;
            temp -= cnt * x1;
            count += cnt;
        }

        while (temp >= a2)
        {
            long cnt = (temp - a2) / x2 + 1;
            temp -= cnt * x2;
            count += cnt;
        }

        return count;
    }
}
