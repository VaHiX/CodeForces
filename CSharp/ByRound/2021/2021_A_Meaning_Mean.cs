// Problem: CF 2021 A - Meaning Mean
// https://codeforces.com/contest/2021/problem/A

/*
Problem: Meaning Mean
Algorithm: Greedy approach with sorting and iterative averaging
Technique: Always pick the two smallest elements to maximize final result

Time Complexity: O(n log n) per test case due to sorting; overall O(t * n log n) where t is number of test cases
Space Complexity: O(n) for storing input array

The key idea is to always combine the two smallest numbers available in each step, which ensures we get the maximum possible final value.
This greedy strategy works because combining smaller numbers early leads to higher accumulated averages.
*/

using System;
using System.Linq;
namespace MeaningMean {
internal class Solution {
  static void Main(string[] args) {
    int limit = int.Parse(Console.ReadLine());
    for (int i = 0; i < limit; i++)
      Solve();
  }
  static void Solve() {
    string size = Console.ReadLine(); // Read the size of array (not used directly, but required for input parsing)
    int[] input1 = Console.ReadLine().Split(' ').Select(int.Parse).ToArray(); // Parse input array
    Array.Sort(input1); // Sort to always have access to smallest elements first
    int answer = input1[0]; // Initialize with first element
    for (int i = 1; i < input1.Length; i++) {
      answer = (answer + input1[i]) / 2; // Combine current answer with next smallest element using floor average
    }
    Console.WriteLine(answer);
  }
}
}


// https://github.com/VaHiX/codeForces/