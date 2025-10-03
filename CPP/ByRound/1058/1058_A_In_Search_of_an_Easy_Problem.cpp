/*
 * Problem URL : https://codeforces.com/contest/1058/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>
int main() {
  int x = 0;
  scanf("%d");
  while (!x && scanf("%d", &x) > 0)
    ;
  printf(x ? "HARD" : "EASY");
}
