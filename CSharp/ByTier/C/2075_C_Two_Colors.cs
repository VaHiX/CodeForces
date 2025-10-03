// Problem: CF 2075 C - Two Colors
// https://codeforces.com/contest/2075/problem/C

/*
C. Two Colors
Purpose: Calculate the number of ways to paint a fence with exactly two colors such that:
- Each plank is painted with exactly one color.
- The number of different colors used is exactly two.
- Planks of the same color form continuous sequences.

Algorithms/Techniques:
- Frequency counting using a list to track how many planks can be painted with each color.
- Cumulative count computation from right to left to efficiently determine valid splits.
- Mathematical inclusion-exclusion principle to calculate combinations without overcounting.
- Prefix sum technique for efficient range queries.

Time Complexity: O(n + m)
Space Complexity: O(n + m)

Input:
t (number of test cases)
n, m (number of planks and number of colors)
a1, a2, ..., am (paint capacity for each color)

Output:
Number of valid ways to paint the fence.
*/
using System;
using System.Linq;
using System.Collections.Generic;
class Program {
  static void Main() {
    int testCases = int.Parse(Console.ReadLine());
    while (testCases-- > 0) {
      string[] inputs = Console.ReadLine().Split();
      int numColors = int.Parse(inputs[0]);
      int numElements = int.Parse(inputs[1]);
      List<int> frequency = new List<int>(new int[numColors + 1]); // Stores count of planks that can be painted with each color
      List<int> colors = Console.ReadLine().Split().Select(int.Parse).ToList();
      foreach (var color in colors) {
        frequency[color]++; // Count how many times each color appears in available paints
      }
      List<int> cumCount = new List<int>(new int[numColors + 2]); // Cumulative count from right to left
      for (int i = numColors; i >= 1; i--) {
        cumCount[i] = frequency[i] + cumCount[i + 1]; // Build cumulative frequency from the end
      }
      long answer = 0;
      for (int splitIndex = 1; splitIndex < numColors; splitIndex++) {
        int leftCount = cumCount[splitIndex];          // Total planks that can be painted with colors 1 to splitIndex
        int rightCount = cumCount[numColors - splitIndex]; // Total planks that can be painted with colors splitIndex+1 to numColors
        int commonCount = cumCount[Math.Max(splitIndex, numColors - splitIndex)]; // Planks which can be painted with both sides (overlapping)
        answer += (long)leftCount * rightCount - commonCount; // Apply inclusion-exclusion principle and accumulate result
      }
      Console.WriteLine(answer);
    }
  }
}


// https://github.com/VaHiX/codeForces/