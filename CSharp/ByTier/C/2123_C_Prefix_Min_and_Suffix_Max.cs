// Problem: CF 2123 C - Prefix Min and Suffix Max
// https://codeforces.com/contest/2123/problem/C

/*
C. Prefix Min and Suffix Max
Algorithm: For each element in the array, determine if it's possible to reduce the entire array to just that element using operations:
- Replace a prefix with its minimum value
- Replace a suffix with its maximum value

Approach:
1. Precompute minLeft[i] = minimum value from index 0 to i
2. Precompute maxRight[i] = maximum value from index i to n-1
3. For each element a[i], it's possible to reduce the array to [a[i]] if:
   - It's the first element (can always be chosen)
   - It equals the minimum of all elements to its left (i.e., minLeft[i] == a[i])
   - It equals the maximum of all elements to its right (i.e., maxRight[i] == a[i])

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case
*/

using System;
class Program {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      int[] a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
      int[] minLeft = new int[n];       // Stores minimum value from start up to index i
      int[] maxRight = new int[n];      // Stores maximum value from index i to end
      minLeft[0] = a[0];
      maxRight[n - 1] = a[n - 1];
      for (int i = 1; i < n; i++) {
        minLeft[i] = Math.Min(minLeft[i - 1], a[i]);  // Build prefix minimums
      }
      for (int i = n - 2; i >= 0; i--) {
        maxRight[i] = Math.Max(maxRight[i + 1], a[i]);  // Build suffix maximums
      }
      char[] result = new char[n];
      for (int i = 0; i < n; i++) {
        // An element can be the final value if:
        // - It's the first element, or
        // - It is the minimum in its prefix, or
        // - It is the maximum in its suffix
        if (i == 0 || a[i] == minLeft[i] || a[i] == maxRight[i]) {
          result[i] = '1';
        } else {
          result[i] = '0';
        }
      }
      Console.WriteLine(new string(result));
    }
  }
}


// https://github.com/VaHiX/CodeForces/