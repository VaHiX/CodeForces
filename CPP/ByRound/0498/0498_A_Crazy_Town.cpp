/*
 * Problem URL : https://codeforces.com/contest/498/problem/A
 * Submit Date : 2025-09-05
 */

/*
 * Problem URL : https://codeforces.com/contest/498/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  double hx, hy;
  scanf("%lf %lf\n", &hx, &hy);
  double ux, uy;
  scanf("%lf %lf\n", &ux, &uy);

  int n;
  scanf("%d\n", &n);
  int steps(0);

  while (n--) {
    double a, b, c;
    scanf("%lf %lf %lf\n", &a, &b, &c);

    if ((a * hx + b * hy + c) * (a * ux + b * uy + c) < 0) {
      ++steps;
    }
  }

  printf("%d\n", steps);

  return 0;
}
