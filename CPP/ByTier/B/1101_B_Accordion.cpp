/*
 * Problem URL : https://codeforces.com/problemset/problem/1101/B
 * Submit Date : 2025-08-18
 */

#import <ios>
int i, s, x, y = 500000;
char p[500001];
int main() {
  for (scanf("%s", p); p[x] ^ 91 && p[x];)
    x++;
  for (; p[y] ^ 93 && y;)
    y--;
  for (; p[x] ^ 58 && p[x];)
    x++;
  for (; p[y] ^ 58 && y;)
    y--;
  if (x >= y) {
    puts("-1");
    return 0;
  }
  for (i = x; i < y; i++)
    s += p[i] == 124;
  printf("%d", s + 4);
}
