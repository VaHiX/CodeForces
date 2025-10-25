/*
 * Problem URL : https://codeforces.com/problemset/problem/429/A
 * Submit Date : 2025-08-16
 */

#include <iostream>
#include <vector>
using namespace std;
#define Mn 101010
bool init[Mn], goal[Mn];
vector<int> v[Mn], z;

int r(int a, int b, bool f1, bool f2) {
  bool f = init[a] ^ goal[a] ^ f1;
  int x = f;
  if (f)
    z.push_back(a);
  for (int c : v[a]) {
    if (c != b)
      x += r(c, a, f2, f ? f1 ^ 1 : f1);
  }
  return x;
}

main() {
  ios::sync_with_stdio(0);
  cin.tie();
  int n, a, b;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }
  for (int i = 1; i <= n; i++)
    cin >> init[i];
  for (int i = 1; i <= n; i++)
    cin >> goal[i];

  cout << r(1, 0, 0, 0) << '\n';
  for (int i : z)
    cout << i << '\n';
}