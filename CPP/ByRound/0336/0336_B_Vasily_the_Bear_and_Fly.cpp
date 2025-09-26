/*
 * Problem URL : https://codeforces.com/contest/336/problem/B
 * Submit Date : 2025-09-06
 */

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  double m, R;
  cin >> m >> R;

  double answer = (m * (m + 1) * (m + 2) / 3 - m) * 2;
  answer += (sqrt(2.0) - 2) * ((m * m - m) + (m * m - m - (m - 1) * 2));
  answer /= (m * m);

  answer *= R;
  cout << setprecision(7) << answer << endl;
  return 0;
}
