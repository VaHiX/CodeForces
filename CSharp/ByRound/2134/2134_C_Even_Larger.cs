// Problem: CF 2134 C - Even Larger
// https://codeforces.com/contest/2134/problem/C

/* 
 * Problem: C. Even Larger
 * Purpose: Modify an array to make it "good" where every subarray of length >= 2 satisfies that sum of elements at even indices is >= sum of elements at odd indices.
 * Algorithm:
 *   - Process the array from left to right in two passes:
 *     1. First pass (even indices): For each pair of adjacent positions, ensure the left element is not greater than the right.
 *        If it is, decrease the left and accumulate the difference.
 *     2. Second pass (odd indices): Adjust elements by comparing neighbors to ensure conditions are met on odd indices.
 *   - Time Complexity: O(n) for each test case.
 *   - Space Complexity: O(n) due to input array storage.
 */

using System.Text;
namespace EvenLarger;
class Program {
  static long Solve() {
    long n = Next();
    long[] a = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = Next();
    long ans = 0;
    // First pass: handle even indices in pairs
    for (int i = 0; i < n - 1; i += 2) {
      if (a[i] > a[i + 1]) {
        ans += a[i] - a[i + 1]; // Count operations needed to make a[i] <= a[i+1]
        a[i] = a[i + 1]; // Update a[i] to match a[i+1]
      }
      if (i > 0 && a[i] > a[i - 1]) {
        ans += a[i] - a[i - 1]; // Count operations needed to make a[i] <= a[i-1]
        a[i] = a[i - 1]; // Update a[i] to match a[i-1]
      }
    }
    // Second pass: handle odd indices
    for (int i = 1; i < n - 1; i += 2) {
      if (a[i - 1] + a[i + 1] > a[i]) {
        ans += a[i + 1] + a[i - 1] - a[i]; // Count operations needed
        long p = Math.Min(a[i + 1], a[i + 1] + a[i - 1] - a[i]); // Minimum decrease from a[i+1] to satisfy condition
        a[i + 1] -= p; // Apply the adjustment
      }
    }
    return ans;
  }
  static void Main(string[] args) {
    long t = Next();
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve());
    writer.Flush();
  }
  static long Next() {
    int c;
    int m = 1;
    long res = 0;
    do {
      c = reader.Read();
      if (c == '-')
        m = -1;
    } while (c < '0' || c > '9');
    res = c - '0';
    while (true) {
      c = reader.Read();
      if (c < '0' || c > '9')
        return m * res;
      res *= 10;
      res += c - '0';
    }
  }
  static readonly StreamReader reader = new(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}


// https://github.com/VaHiX/codeForces/