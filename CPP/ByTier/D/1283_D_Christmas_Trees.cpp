/*
 * Problem URL : https://codeforces.com/problemset/problem/1283/D
 * Submit Date : 2025-08-16
 */

// author : Yogi79
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m, x;
  cin >> n >> m;

  set<int> s;
  queue<array<int, 3>> q;
  vector<int> v;

  for (int i = 0; i < n; i++) {
    cin >> x;
    s.insert(x);
    q.push({x - 1, -1});
    q.push({x + 1, 1});
  }

  ll d = 0;
  array<int, 3> p;

  while (m) {
    p = q.front();
    q.pop();
    if (s.find(p[0]) == s.end()) {
      s.insert(p[0]);
      v.push_back(p[0]);
      d += p[2] + 1;
      q.push({p[0] + p[1], p[1], p[2] + 1});
      --m;
    }
  }
  cout << d << '\n';
  for (int i : v)
    cout << i << ' ';
}