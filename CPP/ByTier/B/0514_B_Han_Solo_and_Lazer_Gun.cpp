/*
 * Problem URL : https://codeforces.com/contest/514/problem/B
 * Submit Date : 2025-09-13
 */

#include <cstdio>
#include <set>

int main() {

  long n;
  double a, b;
  scanf("%ld %lf %lf\n", &n, &a, &b);
  std::set<double> slopes;
  bool vertical = 0;
  while (n--) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    if (x == a) {
      vertical = 1;
    } else {
      slopes.insert((y - b) / (x - a));
    }
  }

  printf("%ld\n", slopes.size() + vertical);

  return 0;
}
