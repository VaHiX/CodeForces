using System;
using System.IO;

namespace C._I_Will_Definitely_Make_It
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Result();
        }
        static void Result()
        {
            var t = int.Parse(Console.ReadLine());
            for (int i = 0; i < t; i++)
            {
                var kn = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();
                var n = kn[0]; //number of towers 
                var k = kn[1]; //start index
                var intArray = Console.ReadLine().Split(" ").Select(int.Parse).ToArray(); //the heights of the towers.
                Console.WriteLine(CalculateResult(n, k, intArray));
            }
        }
        static string CalculateResult(int n, int k, int[] intArray)
        {
            var startTower = intArray[k - 1];
            Array.Sort(intArray);
            var startIndex = 0;
            for (int i = 0; i < n; i++)// we don't need teleport lower towers, so define minimal index
            {
                if (i == n - 1)// It's mean we start from highest one
                    return "YES";
                if (intArray[i + 1] > startTower && intArray[i] == startTower)
                {
                    startIndex = i;
                    break;
                }
            }
            var waterRange = 1;
            for (int i = startIndex + 1; i < n; i++)
            {
                if (intArray[i] == intArray[i - 1])
                    continue;
                var difference = (intArray[i] - startTower);
                if (difference + waterRange <= startTower + 1)
                {
                    startTower = intArray[i];
                    waterRange += difference;
                }
                else
                    return "NO";
            }
            return "YES";
        }
    }
}
