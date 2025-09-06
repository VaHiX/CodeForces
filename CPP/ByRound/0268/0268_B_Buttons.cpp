/*
 * Problem URL : https://codeforces.com/problemset/problem/268/B
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  long long n;
  cin >> n;

  cout << (n - 1) * n * (n + 1) / 6 + n << endl;
  return 0;
}
