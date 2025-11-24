// Problem: CF 1998 E1 - Eliminating Balls With Merging (Easy Version)
// https://codeforces.com/contest/1998/problem/E1

/*
Purpose: This code solves the "E1. Eliminating Balls With Merging (Easy Version)" problem.
         It determines how many distinct final indices can remain after a sequence of operations
         on an array of balls where merging occurs based on specific comparison rules.

Algorithms/Techniques:
- Prefix sum and greedy approach to simulate possible operations.
- For each starting index i, determine which later positions can be the final remaining element in S.

Time Complexity: O(n^2) in the worst case due to nested loops
Space Complexity: O(n) for storing the array and auxiliary vector 'cnt'

*/
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define PI 3.14159265358979323846
#define ll long long int
#define ld long double
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int test = 1;
  cin >> test;
  while (test--) {
    ll n, x;
    cin >> n >> x;
    vector<ll> a(n + 2);
    ll inf = 1e18;
    a[0] = a[n + 1] = inf;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    if (n == 1) {
      cout << "1\n";
      continue;
    }
    vector<int> cnt(n + 10, 0);
    for (int i = 0; i <= n; i++) {
      ll sm = 0;
      int y = -1;
      for (int j = i + 1; j <= n; j++) {
        if (i == 0 && j == n)
          continue;
        sm += a[j];
        if (sm >= a[i]) {
          break;
        }
        if (sm < a[j + 1]) {
          y = j + 1;
        }
      }
      for (int k = i + 1; k < y; k++) {
        cnt[k] = 1;
      }
    }
    int ans = n;
    for (int i = 1; i <= n; i++) {
      ans -= cnt[i];
    }
    cout << ans;
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/