using System;
using System.Linq;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine()!);

        while (t-- > 0)
        {
            int n = int.Parse(Console.ReadLine()!);

            int[] p = Console.ReadLine()!
                .Split()
                .Select(int.Parse)
                .ToArray();

            int[] q = new int[n];
            for (int i = 0; i < n; i++)
            {
                q[i] = (n + 1) - p[i];
            }

            Console.WriteLine(string.Join(" ", q));
        }
    }
}