/*
 * Problem URL : https://codeforces.com/contest/1030/problem/A
 * Submit Date : 2025-08-30
 */



#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  bool hard(false);
  while (n--) {
    int x;
    scanf("%d", &x);
    if (x) {
      hard = true;
      break;
    }
  }

  puts(hard ? "HARD" : "EASY");

  return 0;
}
