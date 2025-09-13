using System;

class Program
{
    static int LeadingZeroCount(long x)
    {
        // Mimic __builtin_clzll by counting leading zeros
        int count = 0;
        for (int i = 63; i >= 0; i--)
        {
            if ((x & (1L << i)) == 0)
                count++;
            else
                break;
        }
        return count;
    }

    static int f(long x)
    {
        return 2 * (63 - LeadingZeroCount(x)) + 3;
    }

    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0)
        {
            long x = long.Parse(Console.ReadLine());
            Console.WriteLine(f(x));
        }
    }
}
