/*
 * Problem URL : https://codeforces.com/problemset/problem/2095/G
 * Submit Date : 2025-08-10
 */

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  const double PI = 3.1415926535;
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<std::pair<double, double>> v(n);
  for (long p = 0; p < n; p++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    v[p] = std::make_pair(x, y);
  }

  sort(v.begin(), v.end());

  double md = 1e30;
  for (long p = k - 1; p < n; p++) {
    double dx = (v[p].first - v[p - k + 1].first);
    double dy = (v[p].second - v[p - k + 1].second);
    double dsq = dx * dx + dy * dy;
    md = (md < dsq ? md : dsq);
  }

  printf("%.8lf\n", PI * md / 4);
}
