// Problem: CF 1957 B - A BIT of a Construction
// https://codeforces.com/contest/1957/problem/B

using System;
/// <summary>
/// Problem: Construct a sequence of n non-negative integers such that their sum equals k,
/// and the number of 1s in the binary representation of their bitwise OR is maximized.
/// 
/// Algorithm:
/// - If n == 1, simply put k in the only element.
/// - Otherwise:
///   - Find the largest power-of-2 minus 1 (like 1, 3, 7, 15, ...) that is less than or equal to k.
///   - Assign this value to the first element.
///   - Assign the remaining sum (k - first_element) to the second element.
/// 
/// Time Complexity: O(log k) per test case due to finding the largest s such that 2*s+1 <= k.
/// Space Complexity: O(n) for storing the array of size n.
/// </summary>
public class ABitOfAConstruction {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      string[] parts = Console.ReadLine().Split();
      int n = int.Parse(parts[0]);
      int k = int.Parse(parts[1]);
      int[] a = new int[n];
      if (n == 1)
        a[0] = k;
      else {
        int s = 1;
        int sNext = 3;
        while (sNext <= k) {
          s = sNext;
          sNext = 2 * sNext + 1; // Generate next number of form (2^m - 1)
        }
        a[0] = s;
        a[1] = k - s; // Remaining sum goes to second element
      }
      Console.WriteLine(string.Join(" ", a));
    }
  }
}

// https://github.com/VaHiX/CodeForces/