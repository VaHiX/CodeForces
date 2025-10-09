/*
 * Problem URL : https://codeforces.com/contest/887/problem/A
 * Submit Date : 2025-08-31
 */

#include <iostream>

int main() {

  const int N = 6;
  std::string s;
  std::cin >> s;
  bool isOne(0);
  int countz(0);
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == '1') {
      isOne = true;
    } else if (s[p] == '0' && isOne) {
      ++countz;
    }
  }

  std::cout << ((isOne && (countz >= N)) ? "yes" : "no") << std::endl;

  return 0;
}
