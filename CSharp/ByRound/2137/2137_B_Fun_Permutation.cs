// Problem: CF 2137 B - Fun Permutation
// https://codeforces.com/contest/2137/problem/B

/*
B. Fun Permutation
Algorithm: Construct a permutation q such that GCD(p[i] + q[i], p[i+1] + q[i+1]) >= 3 for all adjacent pairs.
Technique: Simple transformation - For each element in the input permutation p, compute q[i] = (n + 1) - p[i].
Time Complexity: O(n) per test case, where n is the size of the permutation.
Space Complexity: O(n) for storing the input and output arrays.

This approach works because:
- By setting q[i] = (n + 1) - p[i], we ensure that the sum p[i] + q[i] = n + 1.
- Since n >= 2, we have n + 1 >= 3.
- As long as n + 1 is not divisible by small primes (like 2 or 3), we can guarantee GCD(p[i] + q[i], p[i+1] + q[i+1]) >= 3.
- This is sufficient for the problem since n + 1 will be at least 3 and often coprime with many small numbers.
*/

using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()!); // Read number of test cases
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine()!); // Read size of permutation
      int[] p = Console.ReadLine()!.Split().Select(int.Parse).ToArray(); // Read input permutation
      int[] q = new int[n]; // Initialize result permutation
      for (int i = 0; i < n; i++) {
        q[i] = (n + 1) - p[i]; // Transform each element using the formula
      }
      Console.WriteLine(string.Join(" ", q)); // Output the constructed permutation
    }
  }
}


// https://github.com/VaHiX/codeForces/