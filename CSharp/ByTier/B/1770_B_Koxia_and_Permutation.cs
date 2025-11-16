// Problem: CF 1770 B - Koxia and Permutation
// https://codeforces.com/contest/1770/problem/B

﻿// Purpose: This code solves the problem of constructing a permutation of length n such that the maximum value of the sum of max and min in all contiguous subarrays of length k is minimized.
// Algorithm: The solution uses a greedy strategy to construct the permutation by interleaving the largest and smallest available numbers to balance the max and min values in sliding windows.
// Time Complexity: O(n) for each test case, since we construct the permutation in linear time.
// Space Complexity: O(n) for storing the output permutation for each test case.

using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>(); // List to store output for each test case
    for (int z = 0; z < count; z++) {
      var a = Console.ReadLine().Split(' ').Select(qw => long.Parse(qw)).ToList(); // Read n and k
      List<long> o = new List<long>(); // List to store the constructed permutation
      long k = a[0]; // k is the length of the sliding window (reused as k in the code)
      long n = k / 2; // Half of k, used for loop iterations
      for (int i = 0; i < n; i++) {
        o.Add(k - i); // Add the largest remaining number
        o.Add(i + 1); // Add the smallest remaining number
      }
      if (k % 2 == 1) // If k is odd, add the middle number
        o.Add((k + 1) / 2);
      output.Add(string.Join(" ", o)); // Convert permutation to space-separated string
    }
    string on = string.Join("\n", output); // Join all test case outputs with newlines
    Console.WriteLine(on); // Output all results
  }
}
}


// https://github.com/VaHiX/CodeForces/