/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
#define MAX 1010101
typedef long long ll;
int A[MAX];
int pv[MAX];
int tree[MAX];
int N, M;
void upd(int i, int x) {
  while (i <= N) {
    tree[i] += x, i += i & -i;
  }
}
int get(int i) {
  i = min(i, N);
  int ans = 0;
  while (i) {
    ans += tree[i], i -= i & -i;
  }
  return ans;
}
signed main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N >> M;
  int i;
  for (i = 1; i <= N; i++)
    cin >> A[i];
  for (i = 1; i <= M; i++)
    pv[i] = N + 1;
  ll sum = 0;
  for (i = N; i >= 1; i--) {
    if (pv[A[i]] <= N)
      upd(pv[A[i]], -1);
    upd(i, 1), pv[A[i]] = i;
    if (i == 1)
      break;
    int a = A[i - 1];
    int r = pv[a];
    sum += get(r - 1);
  }
  for (i = 1; i <= M; i++)
    sum += get(pv[i] - 1);
  cout << sum;
}