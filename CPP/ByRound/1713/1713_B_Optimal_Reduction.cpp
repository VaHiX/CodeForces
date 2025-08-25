/*
 * Problem URL : https://codeforces.com/problemset/problem/1713/B
 * Submit Date : 2025-08-13
 */

#include <stdio.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]);
    }

    int i = 0;
    while (i + 1 < n && arr[i + 1] >= arr[i])
      i++;
    while (i + 1 < n && arr[i + 1] <= arr[i])
      i++;
    if (i + 1 == n)
      printf("YES\n");
    else
      printf("NO\n");
  }
}
