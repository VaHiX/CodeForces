// Problem: CF 2136 C - Against the Difference
// https://codeforces.com/contest/2136/problem/C

/*
C. Against the Difference
Purpose: Find the length of the longest "neat" subsequence in an array.
A "neat" subsequence is one that can be split into blocks, where each block consists of all equal elements and its length equals the value of those elements.

Algorithm:
Dynamic Programming with Hash Map:
- For each position i, maintain a dp[i] which represents the maximum length of a neat subsequence ending at or before position i.
- A HashMap (mp) stores for each element value v, a list of indices where that value appears.
- When processing a new element v at index i:
  - Add i to mp[v].
  - If we have at least v occurrences of v, we can form a block of length v starting from some previous position.
  - Update dp[i] by considering the best way to extend a subsequence ending before that block.

Time Complexity: O(n)
Space Complexity: O(n)

*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using static System.Console;
using ll = System.Int64;
int t = int.Parse(ReadLine());
while (t-- > 0) {
  int n = int.Parse(ReadLine());
  var nums = ReadLine().Split().Select(int.Parse).ToArray();
  var mp = new Dictionary<int, List<int>>(); // Maps each value to list of indices where it occurs
  int[] dp = new int[n + 1]; // dp[i] stores max length of neat subsequence up to index i
  for (int i = 1; i <= n; i++) {
    int v = nums[i - 1]; // current value
    if (!mp.ContainsKey(v))
      mp[v] = new List<int>(); // initialize list for this value if not present
    mp[v].Add(i); // add current index to the list
    dp[i] = dp[i - 1]; // default: carry forward previous best
    if (mp[v].Count >= v) { // check if we have enough occurrences to form a block of size v
      // If we can form such a block, update dp[i]
      if (dp[mp[v][mp[v].Count - v] - 1] + v > dp[i]) 
        dp[i] = dp[mp[v][mp[v].Count - v] - 1] + v;
    }
  }
  WriteLine(dp[n]);
}


// https://github.com/VaHiX/codeForces/