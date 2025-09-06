/*
 * Problem URL : https://codeforces.com/contest/712/problem/A
 * Submit Date : 2025-09-02
 */



#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
  long long int n, count = 0;
  long long int i, j, k;

  cin >> n;
  long long int a[n], b[n];

  for (i = 0; i < n; i++)
    cin >> a[i];

  b[n - 1] = a[n - 1];
  for (i = n - 2; i >= 0; i--) {
    b[i] = a[i] + a[i + 1];
  }

  for (i = 0; i < n; i++)
    cout << b[i] << " ";

  return 0;
}
