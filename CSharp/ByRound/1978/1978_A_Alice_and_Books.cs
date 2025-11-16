// Problem: CF 1978 A - Alice and Books
// https://codeforces.com/contest/1978/problem/A

/*
 * Problem: Alice and Books
 * 
 * Approach:
 * - The key insight is that Alice will read the book with the highest number in each pile.
 * - To maximize the sum of pages read, we want to maximize the sum of the maximum elements
 *   from two non-empty piles.
 * - One pile will contain books from index 0 to i (where i < n-1), and the other from index i+1 to n-1.
 * - The maximum in the first pile is a[i], and in the second pile is a[n-1] (since it's the last book).
 * - So the total pages read is a[i] + a[n-1].
 * - We try all possible splits (i from 0 to n-2) and compute the maximum such sum.
 * 
 * Time Complexity: O(n) per test case - we iterate through the array once to check all possible splits.
 * Space Complexity: O(n) - we store the array of book pages.
 * 
 * Algorithms/Techniques: Brute Force with Optimization
 */

using System;
using System.IO;
class Program {
  static void Main() {
    using (
        StreamReader reader = new StreamReader(
            Console
                .OpenStandardInput())) using (StreamWriter writer =
                                                  new StreamWriter(
                                                      Console
                                                          .OpenStandardOutput())) {
      int t = int.Parse(reader.ReadLine());
      while (t-- > 0) {
        Solve(reader, writer);
      }
    }
  }
  static void Solve(StreamReader reader, StreamWriter writer) {
    int n = int.Parse(reader.ReadLine());
    long[] a = new long[n];
    long res = 0;
    string[] inputs = reader.ReadLine().Split(' ');
    for (int i = 0; i < n; i++) {
      a[i] = long.Parse(inputs[i]);
    }
    // Try all possible splits where the first pile ends at index i and second pile starts at i+1
    // The maximum in the second pile is always a[n-1] 
    for (int i = 0; i < n - 1; i++) {
      if (res < (a[i] + a[n - 1]))
        res = a[i] + a[n - 1];
    }
    writer.WriteLine(res);
  }
}


// https://github.com/VaHiX/CodeForces/