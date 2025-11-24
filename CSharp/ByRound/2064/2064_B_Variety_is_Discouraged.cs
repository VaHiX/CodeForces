// Problem: CF 2064 B - Variety is Discouraged
// https://codeforces.com/contest/2064/problem/B

/*
 * Problem: B. Variety is Discouraged
 * 
 * Purpose: 
 *   Given an array 'a', we need to remove at most one contiguous subarray such that 
 *   the resulting array has maximum score. The score of an array is defined as:
 *   (length of array) - (number of distinct elements in array).
 * 
 * Algorithm:
 *   1. Count frequency of each element in the array using a dictionary.
 *   2. Identify positions where elements appear exactly once (these are candidates for being preserved).
 *   3. Find the longest contiguous segment of such unique elements (to minimize final length).
 *   4. If no such segment exists, return 0 to indicate no removal is needed.
 * 
 * Time Complexity: O(n)
 *   - We traverse the array a few times linearly with dictionary operations and counting.
 * Space Complexity: O(n)
 *   - Dictionary to store frequencies and boolean array of size n.
 */

using System.Linq;
using System.Collections.Generic;
using System;

public class hello {
  static void Main() {
    var T = int.Parse(Console.ReadLine().Trim());
    while (T-- > 0) {
      var n = int.Parse(Console.ReadLine().Trim());
      string[] line = Console.ReadLine().Trim().Split(' ');
      var a = Array.ConvertAll(line, int.Parse);
      getAns(n, a);
    }
  }
  
  static void getAns(int n, int[] a) {
    if (n == 1) {
      Console.WriteLine("1 1");
      return;
    }
    
    // Count frequency of each element
    var d = new Dictionary<int, int>();
    foreach (var x in a)
      if (d.ContainsKey(x))
        d[x]++;
      else
        d[x] = 1;

    // Mark positions where element occurs exactly once
    var b = new bool[n];
    for (int i = 0; i < n; i++) {
      if (d[a[i]] == 1)
        b[i] = true;
    }

    // Count total number of unique elements that appear only once
    var tc = b.Count(x => x == true);
    if (tc == 0) {
      Console.WriteLine(0);
      return;
    }

    // Track longest contiguous segment of unique elements
    var f = false;           // flag to check if we're in a segment
    var tL = 0;              // start index of current segment
    var ansL = 0;            // start index of best segment
    var ansr = 0;            // end index of best segment
    var ans = 0;             // length of the best contiguous segment

    if (b[0]) {
      f = true;
      tL = 0;
    }

    for (int i = 1; i < n; i++) {
      if (b[i]) {
        if (!f) {
          f = true;
          tL = i;
        }
      } else {
        if (f) {
          f = false;
          var tt = i - tL;
          if (tt > ans) {
            ans = tt;
            ansL = tL;
            ansr = i - 1;
          }
        }
      }
    }

    // Handle case where the segment ends at last element
    if (f) {
      var ttt = n - tL;
      if (ttt > ans) {
        ansL = tL;
        ansr = n - 1;
      }
    }

    Console.WriteLine("{0} {1}", ansL + 1, ansr + 1);
  }
}


// https://github.com/VaHiX/codeForces/