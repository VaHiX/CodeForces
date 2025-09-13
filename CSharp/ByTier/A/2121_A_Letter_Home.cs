using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());

        while (testCases-- > 0)
        {
            SolveTestCase();
        }
    }

    static void SolveTestCase()
    {
        int[] input = Console.ReadLine().Split().Select(int.Parse).ToArray();
        int n = input[0];
        int start = input[1];

        List<int> points = Console.ReadLine().Split().Select(int.Parse).ToList();

        int minPoint = points.First();
        int maxPoint = points.Last();

        // Total path: from min to max + nearest approach from start
        long distance = (maxPoint - minPoint) + Math.Min(
            Math.Abs(start - minPoint),
            Math.Abs(start - maxPoint)
        );

        Console.WriteLine(distance);
    }
}
