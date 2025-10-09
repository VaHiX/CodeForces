/*
 * Problem URL : https://codeforces.com/contest/451/problem/A
 * Submit Date : 2025-09-05
 */

#include <cstdio>

int main() {

  int n, m;
  scanf("%d %d", &n, &m);
  int smallest = n;
  if (m < n) {
    smallest = m;
  }
  if (smallest % 2) {
    puts("Akshat");
  } else {
    puts("Malvika");
  }
  return 0;
}
