/*
 * Problem URL : https://codeforces.com/problemset/problem/1742/A
 * Submit Date : 2025-08-21
 */

#include <stdio.h>
int t, a, b, c;
int main() {
  for (scanf("%d", &t); t; --t)
    scanf("%d%d%d", &a, &b, &c),
        puts(a + b == c || a + c == b || b + c == a ? "YES" : "NO");
}