// Problem: CF 2118 A - Equal Subsequences
// https://codeforces.com/contest/2118/problem/A

/*
Problem: Construct a perfect bitstring of length n with exactly k '1's.
         A perfect bitstring has equal numbers of '101' and '010' subsequences.

Algorithms/Techniques: Greedy construction
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The solution uses a greedy approach:
- Place k ones followed by (n-k) zeros.
- This ensures that the number of '101' and '010' subsequences are equal.
*/

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) { // Process each test case
      var parts = Console.ReadLine().Split(); // Split input line into n and k
      int n = int.Parse(parts[0]); // Length of the bitstring
      int k = int.Parse(parts[1]); // Number of '1's in the bitstring
      // Output a string with k '1's followed by (n-k) '0's
      Console.WriteLine(new string('1', k) + new string('0', n - k));
    }
  }
}


// https://github.com/VaHiX/codeForces/