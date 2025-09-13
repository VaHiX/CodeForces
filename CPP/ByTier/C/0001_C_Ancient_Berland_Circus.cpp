/*
 * Problem URL : https://codeforces.com/problemset/problem/1/C
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
const double pi = 3.14159265358979;
vector<double> v(105);

int main() {
  double x1, x2, x3, y1, y2, y3;
  double a, b, c;
  double A, B, C;

  v[3] = 60.0;
  v[4] = 45.0;
  for (int i = 5; i <= 100; i++) {
    double r = 180.0 / i;
    v[i] = r;
  }
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
  c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
  C = acos((a * a + b * b - c * c) / (2 * a * b)) * 180 / pi;
  A = acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / pi;
  B = acos((c * c + a * a - b * b) / (2 * c * a)) * 180 / pi;
  for (int i = 3; i <= 100; i++) {
    if (abs(A / v[i] - double(int(A / v[i] + 0.000004))) <= 0.000004 &&
        abs(B / v[i] - int(B / v[i] + 0.000004)) <= 0.000004 &&
        abs(C / v[i] - int(C / v[i] + 0.000004)) <= 0.000004) {
      double n;
      n = c * sin(v[i] * pi / 180) / sin(C * pi / 180);
      cout << fixed << setprecision(8)
           << i * n * n * sin(2 * pi / i) / (4 * (1 - cos(2 * pi / i))) << endl;
      break;
    }
  }
  return 0;
}