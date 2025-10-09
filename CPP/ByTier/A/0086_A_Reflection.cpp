/*
 * Problem URL : https://codeforces.com/problemset/problem/86/A
 * Submit Date : 2025-08-14
 */

#include <iostream>
using namespace std;
int main() {
  long long int l, r, a = 1;
  for (cin >> l >> r; a <= r; a *= 10)
    ;
  l = min(max(a / 2, l), r);
  cout << l * (a - 1 - l);
}
