// Problem: CF 1773 F - Football
// https://codeforces.com/contest/1773/problem/F
//
// This solution constructs a sequence of n match results (format X:Y) given
// target totals `a` (number of wins for team A) and `b` (wins for team B).
// The goal is to output whether it is possible to have a final result where
// team A has `a` wins and team B has `b` wins after n matches, and to
// produce one valid sequence of per-match scores respecting that total. The
// program prints an initial integer (1 or 0) indicating a special tied-case
// possibility for n==1, or prints 0/positive number and an example list of
// per-match scores for the general cases.
//
// Two main cases:
// 1) If a + b <= n: we can place `a` matches with 1:0, `b` matches with 0:1,
//    and the remaining matches as 0:0. The program prints the number of
//    remaining 0:0 matches first, then lists all matches.
// 2) If a + b > n: there are not enough matches to assign unique 1:0 and
//    0:1 outcomes for all wins; the program constructs a sequence that uses
//    multiple matches per team when needed while ensuring the total counts
//    are satisfied and printing 0 on the first line as required by the
//    problem's output format.

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  i64 n;
  cin >> n;
  i64 a, b; // desired totals for team A and team B
  cin >> a >> b;

  // Special-case: single match
  if (n == 1) {
    if (a == b) {
      // Both teams have same wins -> tie allowed (print 1 then score)
      cout << "1\n" << a << ':' << b << '\n';
    } else {
      // Not a tie: impossible special-case, print 0 then the single score
      cout << "0\n" << a << ':' << b << '\n';
    }
    return 0;
  }

  // If sum of wins does not exceed number of matches, simple assignment works.
  if (a + b <= n) {
    // First print how many matches will be 0:0
    cout << n - a - b << '\n';
    // Output `a` matches 1:0
    for (int i = 0; i < a; i++) {
      cout << "1:0\n";
    }
    // Output `b` matches 0:1
    for (int i = 0; i < b; i++) {
      cout << "0:1\n";
    }
    // Remaining matches are 0:0
    for (int i = 0; i < n - a - b; i++) {
      cout << "0:0\n";
    }
  } else {
    // a + b > n: need to craft a sequence where some matches may be
    // "double-counted" effectively to achieve totals. According to the
    // problem's constructive approach, print 0 then output a sequence that
    // places several 1:0 and 0:1 matches and a final block to achieve totals.
    cout << "0\n";
    i64 tmpa = a, tmpb = b;
    int cnt = 0;
    // Greedily output up to n-2 matches of 1:0 (but not exceeding a)
    for (int i = 0; i < min(tmpa, n - 2); i++) {
      cout << "1:0\n";
      cnt++;
      a--;
    }
    n -= cnt; // remaining matches to fill
    // Greedily output up to n-2 matches of 0:1 (but not exceeding b)
    for (int i = 0; i < min(tmpb, n - 2); i++) {
      cout << "0:1\n";
      b--;
    }
    // Now fill the final few matches depending on leftover a and b
    if (a == 0) {
      // No remaining A-wins: print one match with B's remaining wins minus 1,
      // then a final 0:1 to finish the counts
      cout << "0:" << b - 1 << '\n';
      cout << "0:1\n";
    } else if (b == 0) {
      // Symmetric case: no remaining B-wins
      cout << a - 1 << ":0\n";
      cout << "1:0\n";
    } else {
      // Both sides still have leftover wins: place them across two matches
      cout << a << ":0\n0:" << b << '\n';
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/