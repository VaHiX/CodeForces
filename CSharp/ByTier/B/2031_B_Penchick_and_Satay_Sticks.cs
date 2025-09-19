using System;
using System.Collections.Generic;

class Program
{
    static string CheckPositions(int n, List<int> p)
    {
        int[] pos = new int[n + 1];
        for (int j = 0; j < n; j++)
        {
            pos[p[j]] = j + 1;
        }
        for (int i = 1; i <= n; i++)
        {
            if (Math.Abs(pos[i] - i) > 1)
            {
                return "NO";
            }
        }
        return "YES";
    }

    static void Main()
    {
        int testCount = int.Parse(Console.ReadLine());
        List<string> results = new List<string>();
        for (int t = 0; t < testCount; t++)
        {
            int n = int.Parse(Console.ReadLine());
            List<int> p = new List<int>();
            string[] input = Console.ReadLine().Split(' ');
            for (int i = 0; i < n; i++)
            {
                p.Add(int.Parse(input[i]));
            }
            results.Add(CheckPositions(n, p));
        }
        Console.WriteLine(string.Join(Environment.NewLine, results));
    }
}
