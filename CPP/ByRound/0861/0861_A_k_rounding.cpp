/*
 * Problem URL : https://codeforces.com/contest/861/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  long long int n, k;
  cin >> n >> k;
  k = pow(10, k);
  cout << n * (k / __gcd(k, n)) << endl;
  return 0;
}