// Problem: CF 740 B - Alyona and flowers
// https://codeforces.com/contest/740/problem/B

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1, 0);
  for (int p = 1; p <= n; p++) {
    cin >> a[p];
  }
  vector<long> cs(n + 1, 0);
  for (int p = 1; p <= n; p++) {
    cs[p] = cs[p - 1] + a[p];
  }
  long total(0);
  while (m--) {
    int u, v;
    cin >> u >> v;
    long temp = cs[v] - cs[u - 1];
    if (temp > 0) {
      total += temp;
    }
  }
  cout << total << endl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/