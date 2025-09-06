/*
 * Problem URL : https://codeforces.com/problemset/problem/110/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>

typedef long long int ll;

#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<string, int>
#define N 250000

using namespace std;

int main() {

  int i, j, k;
  int n, m, x;

  scanf("%d", &n);

  for (i = 0; i < N; i++) {
    x = n - (i * 4);

    if (x % 7 == 0 && x >= 0) {
      for (j = 0; j < i; j++)
        printf("4");

      for (j = 0; j < x / 7; j++)
        printf("7");

      return 0;
    }
  }

  printf("-1");

  return 0;
}
