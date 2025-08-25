/*
 * Problem URL : https://codeforces.com/problemset/problem/1495/A
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<double> v, w;
    for (long p = 0; p < 2 * n; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      if (x < 0) {
        x = -x;
      };
      if (y < 0) {
        y = -y;
      }
      if (x) {
        v.push_back(x);
      } else {
        w.push_back(y);
      }
    }

    sort(v.begin(), v.end());
    sort(w.begin(), w.end());
    double total(0);
    for (long p = 0; p < n; p++) {
      total += sqrt(v[p] * v[p] + w[p] * w[p]);
    }
    printf("%.11lf\n", total);
  }
}
