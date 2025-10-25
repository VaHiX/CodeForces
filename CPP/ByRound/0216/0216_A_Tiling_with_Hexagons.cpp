/*
 * Problem URL : https://codeforces.com/problemset/problem/216/A
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;
  cout << a * b + b * c + c * a - a - b - c + 1 << endl;
  return 0;
}
