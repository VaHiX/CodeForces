/*
 * Problem URL : https://codeforces.com/problemset/problem/727/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  int arr[10000];
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    printf("? 1 %d \n", i);
    fflush(stdout);
    scanf("%d", &arr[i]);
  }
  int x;
  printf("? 2 3 \n");
  fflush(stdout);
  scanf("%d", &x);
  x = (arr[2] - x + arr[3]) / 2;
  printf("! %d ", x);
  for (int i = 2; i <= n; i++) {
    printf("%d ", arr[i] - x);
  }
  printf("\n");
}