// Problem: CF 2029 C - New Rating
// https://codeforces.com/contest/2029/problem/C

using System;
using System.Linq;
class Solution {
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      var v = Console.ReadLine().Split().Select(int.Parse).ToArray();
      long ns = 0, ss = long.MinValue, s = long.MinValue;
      for (int i = 0; i < n; i++) {
        int x = v[i];
        // Calculate new rating if we don't skip current contest
        long temp_ns;
        temp_ns = (x > ns) ? ns + 1 : (x == ns) ? ns : ns - 1;
        // Update best rating so far
        long temp_ss = Math.Max(ss, ns);
        long temp_s1 = long.MinValue;
        // If we have a skip interval, calculate effect of current contest on that
        if (ss != long.MinValue) {
          temp_s1 = ss + Math.Sign(x - ss);
        }
        long temp_s2 = long.MinValue;
        // If we have a skip interval and the previous one also skipped
        if (s != long.MinValue) {
          temp_s2 = s + Math.Sign(x - s);
        }
        long temp_s = Math.Max(temp_s1, temp_s2);
        // Update all state variables for next iteration
        (ns, ss, s) = (temp_ns, temp_ss, temp_s);
      }
      // Final update: compare final best rating so far with last best
      s = Math.Max(s, ss);
      Console.WriteLine(s);
    }
  }
}


// https://github.com/VaHiX/CodeForces/