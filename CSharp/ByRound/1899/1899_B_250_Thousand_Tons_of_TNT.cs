// Problem: CF 1899 B - 250 Thousand Tons of TNT
// https://codeforces.com/contest/1899/problem/B

/*
 * Problem: B. 250 Thousand Tons of TNT
 * 
 * Algorithm:
 * - For each possible number of boxes per truck k (from 2 to n/2), check if n is divisible by k.
 * - If divisible, calculate total weight for each group of k boxes.
 * - Find min and max total weights among all groups and compute their difference.
 * - Keep track of maximum difference found across all valid k values.
 * 
 * Time Complexity: O(n^2) in worst case due to nested loops over k and groups,
 *                  but since n <= 150000 and we loop up to n/2, and each group calculation is O(1) with prefix sums,
 *                  effectively it's closer to O(n * sqrt(n)) or better depending on divisors of n.
 * Space Complexity: O(n) for storing prefix sums and the array of box weights.
 */

using System;
public class _250ThousandTonsOfTnt {
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      long[] sums = new long[n + 1]; // Prefix sum array to quickly calculate sum of any subarray
      int aMin = 1000000000;
      int aMax = 1;
      for (int j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]);
        a[j] = aj;
        sums[j + 1] = sums[j] + aj; // Build prefix sum
        aMin = Math.Min(aMin, aj);
        aMax = Math.Max(aMax, aj);
      }
      long ans = aMax - aMin; // Initialize with difference of max and min individual weights
      int nHalf = n / 2;
      for (int k = 2; k <= nHalf; k++) {
        if (n % k > 0)
          continue; // Skip if n is not divisible by k - cannot evenly distribute boxes
        long sMin = 75000000000000L; // Initialize to a large value
        long sMax = 2; // Initialize to a small value
        for (int j = 0; j <= n - k; j += k) {
          long s = sums[j + k] - sums[j]; // Calculate sum of k consecutive boxes starting at index j using prefix sum
          sMin = Math.Min(sMin, s);
          sMax = Math.Max(sMax, s);
        }
        ans = Math.Max(ans, sMax - sMin); // Update maximum difference found
      }
      Console.WriteLine(ans);
    }
  }
}


// https://github.com/VaHiX/CodeForces/