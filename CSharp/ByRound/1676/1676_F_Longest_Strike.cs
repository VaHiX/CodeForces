// Problem: CF 1676 F - Longest Strike
// https://codeforces.com/contest/1676/problem/F
 
﻿/*
 * Problem: F. Longest Strike
 * 
 * Purpose: Find the longest continuous range [l, r] such that every number in the range appears at least k times in the array.
 * 
 * Algorithm:
 * 1. Sort the array to group identical elements together.
 * 2. Use a sliding window approach to identify segments where all elements are the same.
 * 3. For each such segment, check if its length is at least k.
 * 4. Keep track of the longest valid interval [l, r] where all elements appear at least k times.
 * 
 * Time Complexity: O(n log n) due to sorting; the while loop is O(n) overall.
 * Space Complexity: O(1) excluding input storage.
 * 
 * Techniques:
 * - Sorting to group equal elements
 * - Sliding window to find valid intervals
 * - Two pointers approach to process segments
 */
 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
 
namespace LongestStrike1676F {
class Program {
  static void Main(string[] args) {
    int t = Int32.Parse(Console.ReadLine()); // Read number of test cases
    for (int p = 0; p < t; p++) {
      string[] input = Console.ReadLine().Split(' ');
      int k = Int32.Parse(input[1]); // Read minimum occurrence count k
      int[] arr = Console.ReadLine().Split(' ').Select(x => Int32.Parse(x)).ToArray(); // Read array elements
      Array.Sort(arr); // Sort the array to group identical elements
      int i = 0; // Initialize pointer
      int[] answer = new int[2]; // Stores the result range [l, r]
      int[] currAnswer = new int[2]; // Stores current valid range being processed
      currAnswer[0] = -1; // Initialize current answer to -1 (indicating invalid)
      answer[0] = -1; // Initialize final answer to -1
      while (i < arr.Length) {
        int startNum = i; // Mark start of current segment
        if (currAnswer[0] != -1 && arr[i] - arr[i - 1] > 1) {
          // If we have a previous valid range and there's a gap, reset current range
          currAnswer[0] = -1;
        }
        // Move i to the end of the current segment (all equal elements)
        while (i + 1 < arr.Length && arr[i] == arr[i + 1])
          ++i;
        // Check if the segment size is at least k (i.e., count of elements)
        if (i - startNum + 1 >= k) {
          if (currAnswer[0] == -1) {
            // Initialize start and end of current valid range
            currAnswer[0] = arr[i];
            currAnswer[1] = arr[i];
          } else {
            // Extend the end of current range
            currAnswer[1] = arr[i];
          }
        } else {
          // Reset current range if segment does not meet k requirement
          currAnswer[0] = -1;
        }
        // Update global answer if current range is longer
        if (currAnswer[0] != -1) {
          if (answer[0] == -1 || answer[1] - answer[0] < currAnswer[1] - currAnswer[0]) {
            answer[0] = currAnswer[0];
            answer[1] = currAnswer[1];
          }
        }
        ++i; // Move to next element
      }
      // Output result
      if (answer[0] == -1)
        Console.WriteLine(-1);
      else
        Console.WriteLine(answer[0] + " " + answer[1]);
    }
  }
}
}
 
 
// https://github.com/VaHiX/CodeForces/