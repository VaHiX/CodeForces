// Problem: CF 1734 D - Slime Escape
// https://codeforces.com/contest/1734/problem/D

/*
Algorithm/Technique:
The problem is about determining whether a slime at position k can escape to either 0 or n+1 without its health ever dropping below zero. The key insight is to use prefix sums and greedy approach to simulate the path.

We process from the starting position k and attempt to move towards the escape points (0 and n+1). We maintain cumulative sums for both sides (left and right) to track minimum health required to move towards each direction. 

We greedily choose to extend our path either to the left (absorbing slimes) or right, depending on which gives a better chance of not going negative. This greedy approach works because we're trying to avoid a negative health state, and prefix sums help us determine when we'd go negative.

Time complexity: O(n) per test case, as we process each element at most twice in the loop.
Space complexity: O(n) for storing prefix sums.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int t, n, k;
long long s[200020]; // prefix sum array
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> s[i];
      s[i] += s[i - 1]; // compute prefix sum
    }
    int l = k - 1, r = k;   // l is leftmost position we can reach, r is rightmost
    long long ls = s[l], rs = s[r]; // ls = min health on left side, rs = max health on right side
    
    while (0 < l && r < n) { // while both pointers are within bounds
      if (s[l - 1] <= rs) 
        // if moving left is better (less negative health), extend left
        ls = min(ls, s[--l]); 
      else if (ls <= s[r + 1])
        // if moving right is better, extend right
        rs = max(rs, s[++r]); 
      else
        // else break if no good direction
        break;
    }
    // if either l == 0 or r == n, we can escape
    puts(0 < l && r < n ? "NO" : "YES");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/