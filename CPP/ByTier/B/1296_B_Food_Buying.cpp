/*
 * Problem URL : https://codeforces.com/problemset/problem/1296/B
 * Submit Date : 2025-08-20
 */

#import <cstdio>
int t, s;
main() {
  for (scanf("%d", &t); t--; printf("%d\n", s + (s - 1) / 9))
    scanf("%d", &s);
}