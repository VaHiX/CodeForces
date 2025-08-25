/*
 * Problem URL : https://codeforces.com/problemset/problem/543/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;

int mat[20][20];
string s[20];
int n, m;
int dp[2000000];

int solve(int mask) {
  if (mask == (1 << n) - 1)
    return 0;
  if (dp[mask] != -1)
    return dp[mask];
  int p = -1;
  for (int i = 0; i < n; i++) {
    if ((mask & (1 << i)) == 0) {
      p = i;
      break;
    }
  }
  dp[mask] = 100000000;
  for (int i = 0; i < m; i++) {
    dp[mask] = min(dp[mask], solve(mask | (1 << p)) + mat[p][i]);
    int valor = 0;
    int maior = 0;
    int par = 0;
    for (int j = 0; j < n; j++) {
      if (s[j][i] == s[p][i]) {
        valor += mat[j][i];
        maior = max(maior, mat[j][i]);
        par |= (1 << j);
      }
    }
    valor -= maior;

    dp[mask] = min(dp[mask], solve(mask | par) + valor);
  }

  // cout<<mask<<" "<<dp[mask]<<endl;

  return dp[mask];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> s[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cin >> mat[i][j];
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(0) << endl;
}
