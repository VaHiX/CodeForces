/*
 * Problem URL : https://codeforces.com/contest/1175/problem/A
 * Submit Date : 2025-08-28
 */

#include <iostream>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long int n, k, c = 0;
    cin >> n >> k;
    while (n)
      c += n % k + 1, n = n / k;
    cout << c - 1 << endl;
  }
  return 0;
}