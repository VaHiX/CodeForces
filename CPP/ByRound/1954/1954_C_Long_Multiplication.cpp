/*
 * Problem URL : https://codeforces.com/problemset/problem/1954/C
 * Submit Date : 2025-08-12
 */

#include <iostream>

int main() {

  long t;
  std::cin >> t;
  while (t--) {
    std::string x, y;
    std::cin >> x >> y;

    bool diff(false);
    for (long p = 0; p < x.size(); p++) {
      if (x[p] == y[p]) {
        continue;
      } else if (!diff) {
        diff = true;
        if (x[p] < y[p]) {
          char tmp = x[p];
          x[p] = y[p];
          y[p] = tmp;
        }
      } else if (x[p] > y[p]) {
        char tmp = x[p];
        x[p] = y[p];
        y[p] = tmp;
      }
    }

    std::cout << x << std::endl << y << std::endl;
  }
}
