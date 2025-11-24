// Problem: CF 1704 D - Magical Array
// https://codeforces.com/contest/1704/problem/D

/*
Algorithm: Magical Array
Purpose: Determine the special array index and number of Operation 2 used on it.
Approach:
1. Process each column of the input arrays to compute differences.
2. Track cumulative shifts for each row.
3. Compute the minimum and maximum values of these cumulative shifts.
4. The index of the minimum value plus 1 gives the special array index.
5. The difference between maximum and minimum values gives number of Operation 2.

Time Complexity: O(n * m), where n is number of arrays and m is length of each array.
Space Complexity: O(n * m), for storing the input data and intermediate calculations.
*/

﻿using System;
using System.Collections.Generic;
using System.Linq;
namespace Compete2 {
partial class MainClass {
  public static void Main(string[] args) {
    int count = int.Parse(Console.ReadLine()); // Read number of test cases
    List<string> output = new List<string>();
    for (int z = 0; z < count; z++) {
      var a = Console.ReadLine().Split(' ').Select(qw => int.Parse(qw)).ToList(); // Read n and m
      List<ulong[]> data = new List<ulong[]>(); // Store input arrays
      for (int i = 0; i < a[0]; i++) {
        data.Add(Console.ReadLine()
                     .Split(' ')
                     .Select(qw => ulong.Parse(qw))
                     .ToArray()); // Read each array
      }
      ulong[] t = new ulong[a[0]]; // Array to store cumulative sums
      List<ulong> shift2 = new List<ulong>(); // Store cumulative shifts
      for (int i = 0; i < a[1]; i++) { // Iterate through each column
        List<ulong> shift = new List<ulong>(); // Temporary storage for column values
        for (int j = 0; j < a[0]; j++) {
          shift.Add(data[j][i]); // Add current element to shift list
          if (shift2.Count > 0)
            shift[shift.Count - 1] += shift2[j]; // Apply previous shift before min calculation
        }
        shift2 = new List<ulong>(); // Reset shift2 for next iteration
        ulong m = shift.Min(); // Find minimum in current column
        for (int j = 0; j < a[0]; j++) {
          t[j] += (shift[j] - m); // Accumulate differences
          shift2.Add(shift[j] - m); // Store shifted value for next column
        }
      }
      ulong mi = t.Min(); // Find minimum cumulative sum
      ulong k = t.Max() - mi; // Difference between max and min gives Operation 2 count
      List<ulong> o = new List<ulong>();
      o.Add(1 + (ulong)Array.IndexOf(t, t.Min())); // Special array index (1-based)
      o.Add(k); // Number of Operation 2 used
      output.Add(string.Join(" ", o));
    }
    output.ForEach(d => Console.WriteLine(d)); // Print all outputs
  }
}
}


// https://github.com/VaHiX/CodeForces/