// Problem: CF 2124 B - Minimise Sum
// https://codeforces.com/contest/2124/problem/B

/*
B. Minimise Sum
Algorithm: Greedy approach to minimize the sum of prefix minimums after at most one operation.
Time Complexity: O(n) per test case, as we process each element once.
Space Complexity: O(n) for storing the array input.

This problem involves minimizing the sum of prefix minimums by performing at most one operation:
Choose two indices i < j, set a[i] := a[i] + a[j], and set a[j] = 0.
We compute all possible outcomes and choose the minimum.
*/

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    for (int testCase = 0; testCase < t; testCase++) {
      int n = int.Parse(Console.ReadLine()); // Read length of array
      int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse); // Read array elements
      
      if (n == 2) {
        // For two elements, only one operation is possible: combine them
        Console.WriteLine(a[0] + Math.Min(a[0], a[1]));
      } else if (a[1] == 0) {
        // If second element is zero, no benefit from combining
        Console.WriteLine(a[0]);
      } else {
        // Try different combinations to find optimal choice
        int option1 = a[0] + Math.Min(a[0], a[1] + a[2]); // Combine a[1] and a[2]
        int option2 = a[0] + a[1]; // Do nothing
        int option3 = a[0] + a[2] + Math.Min(a[0] + a[2], a[1]); // Combine a[0] and a[2]
        int result = Math.Min(Math.Min(option1, option2), option3); // Choose minimum value
        Console.WriteLine(result);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/