// Problem: CF 1980 D - GCD-sequence
// https://codeforces.com/contest/1980/problem/D

/*
 * Problem: GCD-sequence
 * Purpose: Determine if removing exactly one element from an array makes the GCD-sequence non-decreasing.
 * 
 * Algorithm:
 * 1. Compute the initial GCD-sequence of adjacent elements.
 * 2. Find the first position where the sequence breaks non-decreasing property.
 * 3. Try removing one of three possible elements around the failure point:
 *    - Remove the element at index (idx + 1) which is the first element of the violating pair.
 *    - Remove the element at index (idx + 2) which is the second element of the violating pair.
 *    - Remove the element at index (idx) which is before the violating pair.
 * 4. For each case, compute the new GCD-sequence and check if it's non-decreasing.
 * 5. If any of the removals results in a valid non-decreasing sequence, return YES.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
*/
using System;
class GCDProgram {
  static long GCD(long a, long b) {
    if (b == 0)
      return a;
    return GCD(b, a % b);
  }
  static void Main() {
    long testCases = long.Parse(Console.ReadLine());
    for (long t = 1; t <= testCases; t++) {
      long n = long.Parse(Console.ReadLine());
      long[] nums = Array.ConvertAll(Console.ReadLine().Split(), long.Parse);
      long[] gcds = new long[n - 1];
      for (long i = 0; i < n - 1; i++) {
        gcds[i] = GCD(nums[i], nums[i + 1]);
      }
      long idx = -1;
      for (long i = 0; i < n - 2; i++) {
        if (gcds[i] > gcds[i + 1]) {
          idx = i;
          break;
        }
      }
      if (idx == -1) {
        Console.WriteLine("YES");
        continue;
      }
      long[] a1 = new long[n - 1]; // Remove element at idx+1
      long[] a2 = new long[n - 1]; // Remove element at idx+2
      long[] a3 = new long[n - 1]; // Remove element at idx
      long j = 0;
      for (long i = 0; i < n; i++) {
        if (i != idx + 1) {
          a1[j] = nums[i];
          j++;
        }
      }
      j = 0;
      for (long i = 0; i < n; i++) {
        if (i != idx + 2) {
          a2[j] = nums[i];
          j++;
        }
      }
      j = 0;
      for (long i = 0; i < n; i++) {
        if (i != idx) {
          a3[j] = nums[i];
          j++;
        }
      }
      long[] b1 = new long[n - 2];
      long[] b2 = new long[n - 2];
      long[] b3 = new long[n - 2];
      for (long i = 0; i < n - 2; i++) {
        b1[i] = GCD(a1[i], a1[i + 1]); // GCD of sequence after removing idx+1
        b2[i] = GCD(a2[i], a2[i + 1]); // GCD of sequence after removing idx+2
        b3[i] = GCD(a3[i], a3[i + 1]); // GCD of sequence after removing idx
      }
      bool flag1 = true;
      bool flag2 = true;
      bool flag3 = true;
      for (long i = 0; i < n - 3; i++) {
        if (b1[i] > b1[i + 1]) {
          flag1 = false;
          break;
        }
      }
      for (long i = 0; i < n - 3; i++) {
        if (b2[i] > b2[i + 1]) {
          flag2 = false;
          break;
        }
      }
      for (long i = 0; i < n - 3; i++) {
        if (b3[i] > b3[i + 1]) {
          flag3 = false;
          break;
        }
      }
      if (!(flag1 || flag2 || flag3)) {
        Console.WriteLine("NO");
      } else {
        Console.WriteLine("YES");
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/