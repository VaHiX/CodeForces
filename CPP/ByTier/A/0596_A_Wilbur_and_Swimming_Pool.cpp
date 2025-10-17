/*
 * Problem URL : https://codeforces.com/contest/596/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  vector<int> A(n), B(n);
  for (int i = 0; i < n; i++)
    cin >> A[i] >> B[i];
  int ar = -1;
  bool g = false;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (i != j) {
        if (A[i] != A[j] && B[i] != B[j]) {
          ar = abs((A[i] - A[j]) * (B[i] - B[j]));
        }
      }
  cout << ar;
}
