/*
 * Problem URL : https://codeforces.com/contest/281/problem/B
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  long long x, y, n, a = -1, b, i, j;
  cin >> x >> y >> n;
  for (i = 1; i <= n; i++) {
    j = i * x / y;
    if (i * x - j * y > (j + 1) * y - i * x)
      j++;
    if (a == -1 || abs(a * y - b * x) * i > abs(j * y - x * i) * b)
      a = j, b = i;
  }
  cout << a << '/' << b << endl;
}
