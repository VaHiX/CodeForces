/*
 * Problem URL : https://codeforces.com/contest/492/problem/A
 * Submit Date : 2025-09-05
 */

/*
 * Problem URL : https://codeforces.com/contest/492/problem/A
 * Submit Date : 2025-09-02
 */



#include <cmath>
#include <iostream>

int main() {

  long n;
  std::cin >> n;
  long a = 0;
  while (a * (a + 1) * (a + 2) <= 6 * n) {
    ++a;
  };
  --a;
  std::cout << a << std::endl;
  return 0;
}
