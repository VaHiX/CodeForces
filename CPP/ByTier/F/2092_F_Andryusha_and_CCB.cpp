// Problem: CF 2092 F - Andryusha and CCB
// https://codeforces.com/contest/2092/problem/F

/*
F. Andryusha and CCB
Algorithm: Segment tree / prefix analysis / group compression technique
Time Complexity: O(n) amortized per test case due to repeated use of precomputed data and efficient looping
Space Complexity: O(n)

This code processes a binary string and for each prefix, calculates how many ways it can be split into k equal beauty substrings.
Uses grouping of consecutive same characters and difference array techniques to efficiently compute counts.

Key parts:
- Grouping consecutive characters into segments with cd[] indicating if segment is repeated (equal)
- Using difference array qzc[] for efficient interval updates
- Final computation of valid k values using a prefix sum style approach

*/

#include <iostream>

#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;
#define ll long long
const int MAXN = 1e6 + 2;
const int MOD = 998244353;
bool cd[MAXN];      // Tracks if a group is repeated (consecutive same characters)
int qzc[MAXN];      // Difference array for interval updates
char s[MAXN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int casenum;
  cin >> casenum;
  while (casenum--) {
    int n;
    cin >> n;
    cin >> s;
    int cnt = 0;     // Number of groups
    cd[0] = 0;       // First group
    for (int i = 1; i < n; i++) {
      if (s[i] == s[i - 1])
        cd[cnt] = 1;   // True if same as previous
      else
        cnt++, cd[cnt] = 0;  // Move to next group
    }
    for (int i = 0; i <= cnt; i++)
      qzc[i] = 0;    // Reset difference array
    
    // Update qzc with segment intervals using sliding window
    for (int i = 1; i < n; i++) {
      int l = 0, r = 0;
      while (l <= cnt) {
        if (l + i > cnt)
          break;
        qzc[l + i]++;           // Increment start of interval
        if (r + i + 1 <= cnt)   // Decrement end+1 of interval
          qzc[r + i + 1]--;
        r += i + 1;             // Next interval start
        if (cd[l + i])          // If new group is repeated, advance by i only
          l += i;
        else                    // Otherwise advance by i + 1
          l += i + 1;
      }
    }
    
    int cnt0 = 0;     // Current index in groups
    int now = 0;
    cout << 1 << " ";    // k=1 always valid
    
    for (int i = 1; i < n; i++) {
      if (s[i] != s[i - 1]) // If new group begins, update current count
        now += qzc[++cnt0];
      cout << now + i - cnt0 + 1 << ' ';  // Final count for this prefix
    }
    cout << endl;
  }
}


// https://github.com/VaHiX/codeForces/