/*
 * Problem URL : https://codeforces.com/problemset/problem/820/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/820/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/820/A
 * Submit Date : 2025-08-21
 */

#include <iostream>

int main() {

  long c, v0, v1, a, l;
  std::cin >> c >> v0 >> v1 >> a >> l;
  long read(0), step(v0), days(0);
  while (read < c) {
    if (read > 0) {
      read -= l;
    }
    read += step;
    step += a;
    step = (step < v1) ? step : v1;
    ++days;
  }

  std::cout << days << std::endl;

  return 0;
}
