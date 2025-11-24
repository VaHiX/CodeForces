// Problem: CF 2149 C - MEX rose
// https://codeforces.com/contest/2149/problem/C

/* 
 * Problem: C. MEX rose
 * Algorithm: Greedy approach with frequency counting
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the frequency array
 * 
 * The goal is to make the MEX of the array equal to k.
 * MEX is the smallest non-negative integer not present in the array.
 * 
 * Strategy:
 * 1. Count occurrences of each number in the array (up to n).
 * 2. Check how many numbers from 0 to k-1 are missing.
 *    These missing numbers require one operation each to introduce.
 * 3. If we have any elements >= k, those can be changed to values less than k,
 *    which reduces operations needed. Specifically, if there are 'a[k]' such elements,
 *    we may use them to reduce the number of required operations by a[k].
 */

using System.Text;
using System;
using System.IO;
using System.Linq;
namespace MEXrose {
class Program {
  static long Solve() {
    int n = Next(); // Read size of array
    int k = Next(); // Read target MEX value
    int[] a = new int[n + 1]; // Frequency array to count occurrences of each number (0 to n)
    for (int i = 0; i < n; i++)
      a[Next()]++; // Read elements and increment their frequency count
    
    int ans = 0;
    for (int i = 0; i < k; i++) // Count how many numbers from 0..k-1 are missing
      if (a[i] == 0)
        ans++;
    
    a[k] -= ans; // Reduce the count of elements that can be repurposed to satisfy MEX=k
    if (a[k] > 0) // If there are still k's left, they may be used to replace others
      ans += a[k]; // Add remaining surplus to operation count
    
    return ans;
  }
  
  static void Main(string[] args) {
    long t = Next(); // Read number of test cases
    for (int i = 0; i < t; i++)
      writer.WriteLine(Solve()); // Process each test case
    writer.Flush();
  }
  
  static int Next() {
    int c;
    int m = 1;
    int res = 0;
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
  
  static readonly StreamReader reader = new StreamReader(
      Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10);
  static readonly StreamWriter writer =
      new StreamWriter(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
}
}

// https://github.com/VaHiX/CodeForces/