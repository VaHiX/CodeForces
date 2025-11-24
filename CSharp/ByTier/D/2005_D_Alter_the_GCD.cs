// Problem: CF 2005 D - Alter the GCD
// https://codeforces.com/contest/2005/problem/D

// Problem: D. Alter the GCD
// Task: Given two arrays a and b, find the maximum value of gcd(a) + gcd(b) after one swap operation on a subarray.
// Algorithms:
// - Prefix and suffix GCD arrays for efficient range queries.
// - Two-pointer technique to iterate over possible segments and calculate contributions.
// - Optimization using lists to store unique prefix/suffix values and reduce computation.
// Time Complexity: O(n * log(max(a[i], b[i])) + n^2) in worst case due to nested loops and gcd operations
// Space Complexity: O(n)

using System;
using System.Collections.Generic;
using System.Linq;

class Program {
  static void Solve() {
    int n = int.Parse(Console.ReadLine());
    int ans = 0;
    long cnt = 0;
    var a = Console.ReadLine().Split().Select(int.Parse).ToArray();
    var b = Console.ReadLine().Split().Select(int.Parse).ToArray();
    
    // Prefix and suffix arrays for GCDs of prefixes/suffixes of a and b
    var prea = new int[n + 1];
    var preb = new int[n + 1];
    var sufa = new int[n + 1];
    var sufb = new int[n + 1];
    
    // Build prefix arrays
    for (int i = 0; i < n; i++) {
      prea[i + 1] = Gcd(prea[i], a[i]);
      preb[i + 1] = Gcd(preb[i], b[i]);
    }
    
    // Build suffix arrays
    for (int i = n - 1; i >= 0; i--) {
      sufa[i] = Gcd(sufa[i + 1], a[i]);
      sufb[i] = Gcd(sufb[i + 1], b[i]);
    }
    
    // Preprocess prefix arrays to get unique values with their last positions
    var fa = new List<int[]> { new int[] { 0, 0 } };
    var fb = new List<int[]> { new int[] { 0, 0 } };
    
    // Lists to store the segments in which the GCD doesn't change
    var pa = new List<int[]>();
    var pb = new List<int[]>();
    
    for (int i = 0; i <= n; i++) {
      if (i == n || prea[i] != prea[i + 1])
        pa.Add(new int[] { prea[i], i });
      if (i == n || preb[i] != preb[i + 1])
        pb.Add(new int[] { preb[i], i });
    }
    
    // Iterate over right endpoints of segments [l, r]
    for (int r = 1; r <= n; r++) {
      int t = a[r - 1];
      
      // Update fa by computing the GCD of current element and all previous in fa
      for (int i = fa.Count - 1; i >= 0; i--) {
        t = Gcd(t, fa[i][0]);
        fa[i][0] = t;
      }
      
      t = b[r - 1];
      
      // Update fb similarly
      for (int i = fb.Count - 1; i >= 0; i--) {
        t = Gcd(t, fb[i][0]);
        fb[i][0] = t;
      }
      
      // Remove duplicate entries from fa and fb
      fa = RemoveDuplicates(fa);
      fb = RemoveDuplicates(fb);
      
      // Add new elements at position r
      fa.Add(new int[] { 0, r });
      fb.Add(new int[] { 0, r });
      
      // Two pointers to process each segment
      int ipa = 0, ipb = 0, ifa = 0, ifb = 0, lst = -1;
      
      while (true) {
        // Find the minimum index among all active segments
        int u = Math.Min(Math.Min(pa[ipa][1], pb[ipb][1]),
                         Math.Min(fa[ifa][1], fb[ifb][1]));
        if (u >= r)
          break;
        
        if (u > lst) {
          // Calculate current result with given segment
          int res = Gcd(pa[ipa][0], Gcd(fb[ifb][0], sufa[r])) +
                    Gcd(pb[ipb][0], Gcd(fa[ifa][0], sufb[r]));
          
          if (res > ans) {
            ans = res;
            cnt = u - lst;
          } else if (res == ans) {
            cnt += u - lst;
          }
        }
        
        lst = u;
        
        // Advance pointers
        if (pa[ipa][1] == u)
          ipa++;
        if (pb[ipb][1] == u)
          ipb++;
        if (fa[ifa][1] == u)
          ifa++;
        if (fb[ifb][1] == u)
          ifb++;
      }
    }
    
    Console.WriteLine($"{ans} {cnt}");
  }

  // Remove consecutive duplicate entries from list
  static List<int[]> RemoveDuplicates(List<int[]> list) {
    int k = 0;
    for (int i = 0; i < list.Count; i++) {
      if (k > 0 && list[k - 1][0] == list[i][0])
        list[k - 1][1] = list[i][1];
      else
        list[k++] = list[i];
    }
    list.RemoveRange(k, list.Count - k);
    return list;
  }

  // Standard Euclidean GCD algorithm
  static int Gcd(int a, int b) {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
  
  static void Main() {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      Solve();
    }
  }
}


// https://github.com/VaHiX/codeForces/