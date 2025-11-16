// Problem: CF 1822 G1 - Magic Triples (Easy Version)
// https://codeforces.com/contest/1822/problem/G1

/*
 * Problem: Magic Triples (Easy Version)
 * 
 * Algorithm/Approach:
 * - For a triple (i,j,k) to be magic, there must exist a positive integer b such that:
 *   a[i] * b = a[j] and a[j] * b = a[k], which implies a[k] = a[i] * b^2.
 * - So, for each element a[j] in the array, we check all possible values of a[i] such that a[j] = a[i] * b and a[k] = a[i] * b^2.
 * - The key idea is to iterate over all elements in the array and for each element a[j],
 *   we count combinations where a[i] * b = a[j] and a[j] * b = a[k].
 * - We use a frequency map (array 'map') to store counts of each number.
 * - For each unique number j, we look for all valid i such that j = i * b and j * b = k (i.e., j * b^2 = k).
 * - We iterate up to sqrt(max(a)) to limit the search space efficiently.
 * 
 * Time Complexity: O(n * sqrt(max(a)) + n)
 * Space Complexity: O(max(a))
 */

using System;
using System.Collections.Generic;
class Program {
  public static Int64[] map = new Int64[1000005];
  static Int64 input() { return Convert.ToInt64(Console.ReadLine()); }
  static Int64[] input_arr() {
    return Array.ConvertAll(Console.ReadLine().Split(' '),
                            arrTemp => Convert.ToInt64(arrTemp));
  }
  static void solve() {
    Int64 n = input();
    Int64 m = 0;
    HashSet<Int64> st = new HashSet<long>();
    foreach (var item in input_arr()) {
      map[item]++; // Count frequency of each number
      m = Math.Max(m, item);
      st.Add(item);
    }
    Int64 B = (Int64)Math.Sqrt(m); // Square root of maximum element used to bound iteration
    Int64 res = 0;
    foreach (var j in st) {
      // Count of sequences where a[j] occurs 3 times: C(count, 3) * 3! (but it's optimized as map[j] * (map[j]-1) * (map[j]-2))
      res += (map[j] - 2) * map[j] * (map[j] - 1);
      // Enumerate possible b values up to sqrt(max(a)) to find valid triples
      for (int i = 2; i <= B; i++) {
        if (j * i * i <= m + 1) {
          // If i * i * j <= m, then we might have a valid triple (a[i], a[i*b], a[i*b^2])
          res += map[j] * map[j * i] * map[j * i * i];
        } else {
          break; // No point in continuing if the value exceeds limit
        }
      }
    }
    Console.WriteLine(res);
    foreach (var j in st) {
      map[j] = 0; // Reset the map for next test case
    }
  }
  static void Main(string[] args) {
    int t = Convert.ToInt32(Console.ReadLine());
    while (t-- > 0) {
      solve();
    }
  }
}


// https://github.com/VaHiX/CodeForces/