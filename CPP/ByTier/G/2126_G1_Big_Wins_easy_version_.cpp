/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/G1
 * Submit Date : 2025-08-08
 */

#include <iostream>
using namespace std;
const int N = 200001;
int A[N], Pre[N], Max[N], Min[N];
int Solve() {
  int n, Ans = 0;
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  for (int i = 1; i <= 100; i++) {
    for (int j = 1; j <= n; j++)
      Pre[j] = Pre[j - 1] + (A[j] >= i ? 1 : -1);
    Min[0] = 0, Max[n] = Pre[n];
    for (int j = 1; j <= n; j++)
      Min[j] = min(Min[j - 1], Pre[j]);
    for (int j = n - 1; j >= 1; j--)
      Max[j] = max(Max[j + 1], Pre[j]);
    for (int j = 1; j <= n; j++)
      if (Min[j - 1] <= Pre[j] || Pre[j - 1] <= Max[j])
        Ans = max(Ans, i - A[j]);
  }
  return Ans;
}
int main() {
  int T;
  cin >> T;
  while (T--)
    cout << Solve() << endl;
  return 0;
}