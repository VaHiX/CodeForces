/*
 * Problem URL : https://codeforces.com/contest/1906/problem/M
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  long long sm = 0;
  int N, x, mx = 0;
  ios::sync_with_stdio(0);
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> x, sm += x, mx = max(mx, x);
  cout << min(sm / 3, sm - mx) << endl;
}