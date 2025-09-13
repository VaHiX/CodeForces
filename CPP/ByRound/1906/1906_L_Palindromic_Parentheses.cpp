/*
 * Problem URL : https://codeforces.com/contest/1906/problem/L
 * Submit Date : 2025-09-07
 */

#include <iostream>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  if (k * 2 < n || k == n)
    cout << -1;
  else {
    for (int i = 0; i < (k - n / 2 + 1) / 2; i++)
      cout << "()";
    for (int i = 0; i < n - k; i++)
      cout << "(";
    for (int i = 0; i < n - k; i++)
      cout << ")";
    for (int i = 0; i < (k - n / 2) / 2; i++)
      cout << "()";
  }
}
