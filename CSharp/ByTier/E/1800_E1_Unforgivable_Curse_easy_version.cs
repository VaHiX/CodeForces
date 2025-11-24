// Problem: CF 1800 E1 - Unforgivable Curse (easy version)
// https://codeforces.com/contest/1800/problem/E1

using System;
using System.Linq;
namespace myApp {
class Solution {
  public static void Main(string[] args) {
    int t = int.Parse(Console.ReadLine());
    while (t > 0) {
      t--;
      Solve();
    }
  }
  public static void Solve() {
    // Read n and k (k is always 3 in this problem)
    int n, k;
    int[] a = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);
    n = a[0];
    k = a[1];
    string s, t;
    s = Console.ReadLine();
    t = Console.ReadLine();
    
    // Check if it's possible to transform s into t by comparing sorted characters
    // If the sorted characters don't match, transformation is impossible
    string st1 = string.Join("", s.OrderBy(c => c)); // Sort characters of s
    string st2 = string.Join("", t.OrderBy(c => c)); // Sort characters of t
    if (st1 != st2) {
      Console.WriteLine("NO");
      return;
    }
    
    // For each position i, check if we can swap s[i] to match t[i]
    // Based on allowed swaps (distance k or k+1), we check if i can reach i+k or i-k
    for (int i = 0; i < n; i++) {
      if (s[i] == t[i])
        continue; // Already correct character, no need to move
        
      // If we can't make a valid move (i-k < 0 and i+k >= n), then it's impossible
      if (i - k >= 0 || i + k < n)
        continue; // Valid move possible
      
      Console.WriteLine("NO");
      return;
    }
    Console.WriteLine("YES");
  }
}
}
/*
Algorithm: Greedy + Sorting Check + Position Validation
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the sorted strings and input strings

The approach works as follows:
1. First, we compare the sorted characters of both strings. If they differ, the transformation is impossible.
2. Then for each character position, we check whether the current character matches the target one.
3. If not, we determine if we can reach that position using valid moves (distance k or k+1).
*/

// https://github.com/VaHiX/CodeForces/