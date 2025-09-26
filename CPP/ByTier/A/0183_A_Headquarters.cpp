/*
 * Problem URL : https://codeforces.com/contest/183/problem/A
 * Submit Date : 2025-09-07
 */

#include "bits/stdc++.h"
using namespace std;

#ifndef LOCAL
#define debug(x...) 22
#endif

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N;
  cin >> N;
  int X = 1, Y = 1;

  for (int i = 0; i < N; ++i) {
    string S;
    cin >> S;

    if (S == "ULDR")
      ++X, ++Y;
    else if (S == "UR" || S == "DL")
      ++X;
    else
      ++Y;
  }
  cout << 1LL * X * Y;
}
