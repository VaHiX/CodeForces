/*
 * Problem URL : https://codeforces.com/contest/678/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  long n, k;
  scanf("%ld %ld\n", &n, &k);
  printf("%ld\n", (1 + n / k) * k);

  return 0;
}
