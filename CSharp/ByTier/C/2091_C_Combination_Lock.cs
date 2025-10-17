// Problem: CF 2091 C - Combination Lock
// https://codeforces.com/contest/2091/problem/C

/*
C. Combination Lock
Algorithm: For odd n, construct a specific permutation that satisfies the condition of exactly one fixed point in every cyclic shift.
For even n, it's impossible to have such a permutation, so return -1.

Time Complexity: O(n) per test case, as we generate a list of size n and print it.
Space Complexity: O(n) for storing the result list.

Techniques:
- Generate a specific sequence that meets problem constraints
- Handle edge cases (even numbers)
*/

using System.Collections.Generic;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim()); // Read number of test cases
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim()); // Read n for current test case
      getAns(n); // Process and output answer for this n
    }
  }
  static void getAns(int n) {
    if (n % 2 == 0) { // Even numbers cannot produce valid permutations
      Console.WriteLine(-1);
      return;
    }
    var ans = new List<int>() { 1 }; // Start with 1
    for (int i = n; i >= 2; i--) // Add elements from n down to 2
      ans.Add(i);
    Console.WriteLine(string.Join(" ", ans)); // Print the constructed permutation
  }
}


// https://github.com/VaHiX/codeForces/