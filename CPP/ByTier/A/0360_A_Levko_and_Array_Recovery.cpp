/*
 * Problem URL : https://codeforces.com/contest/360/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
int arr[5010];
int xx[5010];
int main() {
  int i, j, N, M, t, l, r, x, value, z, k;
  scanf("%d %d", &N, &M);
  for (i = 1; i <= N; i++) {
    arr[i] = 1000000000;
  }
  k = 0;
  for (i = value = 1; i <= M; i++) {
    scanf("%d %d %d %d", &t, &l, &r, &x);
    if (t == 1) {
      for (; l <= r; l++) {
        xx[l] += x;
      }
      k = 1;
    } else {
      for (z = 0; l <= r; l++) {
        if (arr[l] >= x - xx[l]) {
          z = 1;
          arr[l] = x - xx[l];
        }
      }
      value &= z;
    }
  }
  if (value == 1 && (k || M == 1)) {
    printf("YES\n");
    for (i = 1; i <= N; i++) {
      printf("%d ", arr[i]);
    }
  } else {
    printf("NO");
  }
  return 0;
} /*1698335480.8348367*/