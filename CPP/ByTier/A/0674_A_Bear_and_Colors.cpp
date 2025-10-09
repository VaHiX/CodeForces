/*
 * Problem URL : https://codeforces.com/contest/674/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
int frq[N], n, arr[N], mx, ans[N], best;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < n; i++) {
    memset(frq, 0, sizeof(frq));
    mx = best = -1;
    for (int j = i; j < n; j++) {
      frq[arr[j]]++;
      if (frq[arr[j]] > mx || (frq[arr[j]] == mx && arr[j] < best)) {
        mx = frq[arr[j]];
        best = arr[j];
      }
      ans[best]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
  return 0;
}