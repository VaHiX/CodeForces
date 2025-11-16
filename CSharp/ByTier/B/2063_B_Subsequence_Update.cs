// Problem: CF 2063 B - Subsequence Update
// https://codeforces.com/contest/2063/problem/B

/*
B. Subsequence Update
Algorithms/Techniques: Brute-force with sorting and subsequence manipulation
Time Complexity: O(n * log(n)) per test case due to sorting operations
Space Complexity: O(n) for storing arrays and subarrays

The problem asks us to minimize the sum of a segment [l, r] after reversing any subsequence once.
We consider two possible approaches:
1. Sort the left part up to index r and take first (r - l + 1) elements
2. Sort the right part from index l onwards and take first (r - l + 1) elements
Then we compute the minimum of the two sums.
*/
using System;
using System.Linq;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine()); // Read number of test cases
    while (t-- > 0) {
      string[] input = Console.ReadLine().Split(); // Read n, l, r
      int n = int.Parse(input[0]);
      int l = int.Parse(input[1]);
      int r = int.Parse(input[2]);
      long[] arr = Console.ReadLine().Split().Select(long.Parse).ToArray(); // Read array elements
      l--; // Convert to 0-based indexing
      r--;
      // Create left part: from start to r (inclusive)
      long[] leftPart = arr.Take(r + 1).ToArray();
      Array.Sort(leftPart); // Sort left part
      // Create right part: from l (inclusive) to end
      long[] rightPart = arr.Skip(l).ToArray();
      Array.Sort(rightPart); // Sort right part
      
      // Take first (r - l + 1) elements from each sorted array and sum them
      long leftSum = leftPart.Take(r - l + 1).Sum();
      long rightSum = rightPart.Take(r - l + 1).Sum();
      
      Console.WriteLine(Math.Min(leftSum, rightSum)); // Output the minimum of the two sums
    }
  }
}


// https://github.com/VaHiX/codeForces/