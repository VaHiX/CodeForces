// Problem: CF 1834 C - Game with Reversing
// https://codeforces.com/contest/1834/problem/C

/*
Purpose: This code solves the problem of a game between Alice and Bob where they manipulate two strings S and T with the goal of making them equal. 
         Alice changes one character in either string per turn, while Bob reverses one of the strings. 
         The game ends when the strings are equal. The task is to determine the minimum possible duration of the game when both players play optimally.

Algorithm:
- For the original strings S and T, count the number of differing positions (nd).
- Reverse T and count the number of differing positions again (rd).
- Based on the parity of nd and rd, compute two possible game durations:
  - The first duration is based on Alice's optimal turn when she must make moves to resolve mismatches.
  - The second duration is based on Bob's optimal turn when he can reverse one of the strings to potentially reduce mismatches more efficiently.
- Return the minimum of these two durations.

Time Complexity: O(n) for each test case where n is the length of the strings.
Space Complexity: O(n) for storing the strings and their reversals.
*/
#include <iostream>
#include <algorithm>
#include <string>

#define all(x) (x).begin(), (x).end()
#define yes cout << "YES" << '\n'
#define no cout << "NO" << '\n'
#define ll long long
#define mod 1000000007
using namespace std;
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    int nd = 0, rd = 0;
    // Count initial number of differing positions
    for (int i = 0; i < n; i++) {
      if (s1[i] != s2[i]) {
        nd++;
      }
    }
    // Reverse string T and recount differing positions
    reverse(s2.begin(), s2.end());
    for (int i = 0; i < n; i++) {
      if (s1[i] != s2[i]) {
        rd++;
      }
    }
    int ans1, ans2;
    // Compute duration based on Alice's optimal strategy for the original string
    if (nd % 2) {
      ans1 = 2 * nd - 1;
    } else {
      ans1 = 2 * nd;
    }
    // Compute duration based on Bob's optimal strategy
    if (rd == 0) {
      ans2 = 2;
    } else {
      if (rd % 2) {
        ans2 = 2 * rd;
      } else {
        ans2 = 2 * rd - 1;
      }
    }
    cout << min(ans1, ans2) << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/