/*
 * Problem URL : https://codeforces.com/problemset/problem/1047/A
 * Submit Date : 2025-08-14
 */

#import <ios>
int n, a;
main() {
  scanf("%d", &n);
  ++a += n % 3 == 2;
  printf("1 %d %d", a, n - 1 - a);
}