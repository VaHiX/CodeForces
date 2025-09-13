using System;
using System.Linq;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        int testCases = int.Parse(Console.ReadLine());
        
        while (testCases-- > 0)
        {
            string[] inputs = Console.ReadLine().Split();
            int numColors = int.Parse(inputs[0]);
            int numElements = int.Parse(inputs[1]);

            // Initialize frequency and colors
            List<int> frequency = new List<int>(new int[numColors + 1]);
            List<int> colors = Console.ReadLine().Split().Select(int.Parse).ToList();

            // Count frequency of each color
            foreach (var color in colors)
            {
                frequency[color]++;
            }

            // Initialize cumulative count array
            List<int> cumCount = new List<int>(new int[numColors + 2]);
            for (int i = numColors; i >= 1; i--)
            {
                cumCount[i] = frequency[i] + cumCount[i + 1];
            }

            // Calculate the final result
            long answer = 0;
            for (int splitIndex = 1; splitIndex < numColors; splitIndex++)
            {
                int leftCount = cumCount[splitIndex];
                int rightCount = cumCount[numColors - splitIndex];
                int commonCount = cumCount[Math.Max(splitIndex, numColors - splitIndex)];

                answer += (long)leftCount * rightCount - commonCount;
            }

            Console.WriteLine(answer);
        }
    }
}
