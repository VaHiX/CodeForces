/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

long long convert(long long x) {
  long long temp(0), output(0);
  while (x > 0) {
    if (x % 10) {
      temp = 10 * temp + (x % 10);
    };
    x /= 10;
  }
  while (temp > 0) {
    output = 10 * output + (temp % 10);
    temp /= 10;
  }
  return output;
}

int main() {
  long long a, b;
  scanf("%lld %lld", &a, &b);
  (convert(a) + convert(b) == convert(a + b)) ? puts("YES") : puts("NO");
  return 0;
}
