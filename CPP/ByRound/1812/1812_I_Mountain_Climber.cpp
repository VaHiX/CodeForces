// Problem: CF 1812 I - Mountain Climber
// https://codeforces.com/contest/1812/problem/I

/*
 * Problem: Mountain Climber
 * Algorithm/Technique: Simulation with balance tracking
 * 
 * The problem simulates a "mountain climber" where certain letters contribute
 * to climbing (positive direction) and others to descending (negative direction).
 * 
 * We maintain a counter 'cnt' that tracks the current altitude:
 * - Letters 'b', 'd', 'l', 't', 'k', 'f', 'h' add 1 to the altitude (climbing up)
 * - Letters 'g', 'j', 'p', 'q', 'y' subtract 1 from the altitude (descending down)
 * 
 * At any point if altitude goes below zero, the string is invalid.
 * At the end, the altitude must be exactly zero to be valid.
 * 
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(1) - only using a fixed number of variables
 */
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
typedef long long LL;
const int N = 1010, P = 1e9 + 7;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    bool flag = true;
    int cnt = 0;
    for (auto c : s) {
      if (c == 'b' || c == 'd' || c == 'l' || c == 't' || c == 'k' ||
          c == 'f' || c == 'h')
        cnt++; // climbing up
      else if (c == 'g' || c == 'j' || c == 'p' || c == 'q' || c == 'y')
        cnt--; // descending down
      if (cnt < 0)
        flag = false; // invalid if altitude goes below 0
    }
    if (flag && cnt == 0)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/