/*
 * Problem URL : https://codeforces.com/problemset/problem/317/A
 * Submit Date : 2025-08-16
 */

#include <cstdio>
using namespace std;
#define LL long long
int main() {
  LL a, b, c, m, o = 0;
  scanf("%I64d%I64d%I64d", &a, &b, &m);
  if (a < b) {
    c = a;
    a = b;
    b = c;
  }
  if (a >= m) {
    puts("0");
    return 0;
  }
  if (a <= 0) {
    puts("-1");
    return 0;
  }
  if (b < 0) {
    o = 1 - b / a;
    b += a * o;
  }
  while (a < m) {
    c = a;
    a += b;
    b = c;
    ++o;
  }
  printf("%I64d\n", o);
}