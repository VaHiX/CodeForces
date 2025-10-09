// Problem: CF 2044 E - Insane Problem
// https://codeforces.com/contest/2044/problem/E

// **********************************************************************
// Problem: E. Insane Problem
// Purpose: Count the number of ordered pairs (x, y) such that:
//          1. l1 <= x <= r1
//          2. l2 <= y <= r2
//          3. There exists a non-negative integer n such that y = x * k^n
//
// Algorithm: 
//   - For each power of k (k^0, k^1, k^2, ...), compute how many valid (x, y) pairs satisfy y = x * k^n
//   - Use inclusion-exclusion principle via helper function 'calc' to count how many x in [L1, r1] 
//     and corresponding y = x * k^n fall in [l2, r2]
//   - Sum over all valid powers of k until k^n exceeds max(r1, r2)
//
// Time Complexity: O(log(max(r1, r2)) * log(k)) per test case due to increasing powers of k
// Space Complexity: O(1) - only using a constant amount of variables
// **********************************************************************

using static System.Math;
using System;
public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      string[] line = Console.ReadLine().Trim().Split(' ');
      var k = int.Parse(line[0]);
      var L1 = int.Parse(line[1]);
      var r1 = int.Parse(line[2]);
      var L2 = int.Parse(line[3]);
      var r2 = int.Parse(line[4]);
      getAns(k, L1, r1, L2, r2);
    }
  }

  // Helper function to count valid pairs for a fixed power t = k^n
  // t = k^n, we compute how many x in [L1, r1] have corresponding y = x*t in [l2, r2]
  static int calc(long t, int L1, int r1, int L2, int r2) {
    var wL = L2 % t == 0 ? L2 / t : L2 / t + 1; // minimum x such that x*t >= L2
    var wr = r2 / t;                            // maximum x such that x*t <= r2
    var wwL = Max(L1, wL);                      // adjust for x range [L1, r1]
    var wwr = Min(r1, wr);                      // adjust for x range [L1, r1]
    return (int)Max(0, wwr - wwL + 1);          // count of valid x values
  }

  // Main function to compute answer for given parameters
  static void getAns(int k, int L1, int r1, int L2, int r2) {
    var t = 1L;                                 // current power of k
    var rmax = Max(r1, r2);                     // max of ranges for early stopping
    var ans = calc(t, L1, r1, L2, r2);          // count for k^0 case

    while (true) {
      t *= k;                                   // next power of k
      if (t > rmax) break;                      // stop if exceeds max range
      var w = calc(t, L1, r1, L2, r2);          // count valid pairs for this k^n
      ans += w;                                 // accumulate total
    }
    
    Console.WriteLine(ans);
  }
}


// https://github.com/VaHiX/codeForces/