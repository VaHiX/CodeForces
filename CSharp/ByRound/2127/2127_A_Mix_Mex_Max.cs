// Problem: CF 2127 A - Mix Mex Max
// https://codeforces.com/contest/2127/problem/A

/*
 * Problem: A. Mix Mex Max
 * Purpose: Determine if an array with missing elements (-1) can be made "good" by replacing -1s.
 *          An array is good if for every triplet of consecutive elements:
 *          mex(triplet) == max(triplet) - min(triplet)
 * 
 * Algorithm / Techniques:
 * - For each test case, process the array and count occurrences of non-negative integers.
 * - Skip all -1 values when counting.
 * - If there's a 0 in the available numbers, output "NO" immediately (because mex will be 0).
 * - If more than one distinct value is present, output "NO".
 * - Otherwise, output "YES".
 *
 * Time Complexity: O(n log n) per test case due to SortedDictionary operations.
 * Space Complexity: O(n) for storing the frequency map and input array.
 */

namespace Name {
class Program {
  static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t-- > 0) {
      int n = int.Parse(Console.ReadLine());
      string[] a = Console.ReadLine().Split();
      SortedDictionary<int, int> mp = new SortedDictionary<int, int>();
      for (int i = 0; i < n; i++) {
        int x = int.Parse(a[i]);
        if (x == -1)
          continue;
        if (mp.ContainsKey(x))
          mp[x]++;
        else
          mp[x] = 1;
      }
      if (mp.ContainsKey(0)) {   // If 0 is present, mex will always be 0 -> not good
        Console.WriteLine("NO");
        continue;
      }
      Console.WriteLine(mp.Count() > 1 ? "NO" : "YES");   // Only one unique element or all -1s -> can make it good
    }
  }
}
}


// https://github.com/VaHiX/codeForces/