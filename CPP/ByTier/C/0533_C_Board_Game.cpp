/*
 * Problem URL : https://codeforces.com/problemset/problem/533/C
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long a, b, c, d;
  scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
  puts((d >= a + b) || (c >= a + b) || (c >= a && d >= b) ? "Polycarp"
                                                          : "Vasiliy");

  return 0;
}
