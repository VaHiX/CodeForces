/*
 * Problem URL : https://codeforces.com/problemset/problem/253/C
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream fin("input.txt");
  ofstream fout("output.txt");
  int n;
  fin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++)
    fin >> a[i], a[i]++;
  int ret = INT_MAX;
  int r1, c1, r2, c2;
  fin >> r1 >> c1 >> r2 >> c2;
  for (int i = 1; i <= n; i++) {
    int cur = c1;
    for (int j = min({i, r1, r2}); j <= max({i, r1, r2}); j++)
      cur = min(cur, a[j]);
    ret = min(ret, abs(i - r1) + abs(i - r2) + abs(cur - c2));
  }
  fout << ret << "\n";
  return 0;
}