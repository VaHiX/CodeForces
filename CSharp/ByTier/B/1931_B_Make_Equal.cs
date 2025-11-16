// Problem: CF 1931 B - Make Equal
// https://codeforces.com/contest/1931/problem/B

using System;
public class MakeEqual {
  /*
  * Problem: Determine if it's possible to make all containers have equal water amounts
  *          by pouring water from container i to j where i < j.
  * 
  * Algorithm:
  * - The key insight is that we can only pour water forward (from left to right).
  * - If we process containers from left to right and keep a running deficit (d),
  *   then we must ensure that at no point does the cumulative deficit become negative.
  * - The total water is divisible by n, so each container should have exactly sum/n units.
  * 
  * Time Complexity: O(n) per test case, O(n) overall for all test cases
  * Space Complexity: O(n) for storing the array of container amounts
  */
  public static void Main() {
    short t = short.Parse(Console.ReadLine());
    for (short i = 0; i < t; i++) {
      int n = int.Parse(Console.ReadLine());
      string[] parts = Console.ReadLine().Split();
      int[] a = new int[n];
      long sum = 0;
      for (int j = 0; j < n; j++) {
        int aj = int.Parse(parts[j]);
        a[j] = aj;
        sum += aj;
      }
      int waterEqu = Convert.ToInt32(sum / n);
      bool ans = true;
      long d = 0;
      for (int j = 0; j < n && ans; j++) {
        d += a[j] - waterEqu;  // cumulative deficit or surplus
        ans = ans && (d >= 0); // if deficit ever becomes negative, impossible
      }
      Console.WriteLine(ans ? "YES" : "NO");
    }
  }
}

// https://github.com/VaHiX/CodeForces/