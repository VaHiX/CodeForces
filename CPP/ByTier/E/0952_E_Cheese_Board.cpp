/*
 * Problem URL : https://codeforces.com/contest/952/problem/E
 * Submit Date : 2025-09-12
 */

#include <algorithm>
#include <cmath>
#include <iostream>

int main() {

  int hard = 0, soft = 0;
  long n;
  std::cin >> n;

  while (n--) {
    std::string cheese, kind;
    std::cin >> cheese >> kind;
    if (kind == "soft") {
      ++soft;
    } else {
      ++hard;
    }
  }

  long ans = std::max(2 * std::max(hard, soft) - 1, hard + soft);
  ans = ceil(sqrt(ans));
  std::cout << ans << std::endl;

  return 0;
}
