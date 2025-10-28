// Problem: CF 2060 D - Subtract Min Sort
// https://codeforces.com/contest/2060/problem/D

/*
D. Subtract Min Sort

Algorithm:
The problem asks whether we can make a sequence non-decreasing by repeatedly subtracting the minimum of two adjacent elements from both of them. The key insight is that if we process the array from left to right, at each step we subtract min(a[i], a[i+1]) from both a[i] and a[i+1]. This operation ensures that a[i] becomes smaller or equal to a[i+1], but in the process we might reduce a[i] below its current value.

Time Complexity: O(n) - We process each element once.
Space Complexity: O(1) - Only using a constant amount of extra space (excluding input storage).

Techniques:
- Greedy approach with simulation
- Linear scan from left to right

*/

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read length of array
      string[] line = Console.ReadLine().Trim().Split(' '); // Read the array elements
      var a = Array.ConvertAll(line, int.Parse); // Convert string array to int array
      getAns(n, a); // Process the array
    }
  }
  static void getAns(int n, int[] a) {
    for (int i = 0; i < n - 1; i++) { // Iterate through array up to second last element
      if (a[i] > a[i + 1]) { // If current element is greater than next one
        Console.WriteLine("NO"); // It's impossible to sort it this way
        return;
      }
      var w = Min(a[i], a[i + 1]); // Find the smaller of two adjacent elements
      a[i] -= w; // Subtract w from current element
      a[i + 1] -= w; // Subtract w from next element
    }
    Console.WriteLine("YES"); // If loop completes, array can be made non-decreasing
  }
}


// https://github.com/VaHiX/codeForces/