/*
 * Problem URL : https://codeforces.com/problemset/problem/2095/F
 * Submit Date : 2025-08-10
 */

#include <cmath>
#include <cstdio>

int main() {

  long long a, b;
  scanf("%lld %lld", &a, &b);
  printf("%lld\n", 12 * a + 14 * a * b + std::abs(a - b) + (a - 3 * b) * b + 2);
}
