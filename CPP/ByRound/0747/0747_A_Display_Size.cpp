/*
 * Problem URL : https://codeforces.com/contest/747/problem/A
 * Submit Date : 2025-09-02
 */

/*
 * Problem URL : https://codeforces.com/contest/747/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>

int main() {

  long n;
  std::cin >> n;
  long a(1), b(n);
  for (long p = 2; p * p <= n; p++) {
    if (n % p == 0) {
      a = p;
      b = n / p;
    }
  }

  std::cout << a << " " << b << std::endl;

  return 0;
}
