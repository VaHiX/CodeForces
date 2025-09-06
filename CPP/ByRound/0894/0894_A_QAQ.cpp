/*
 * Problem URL : https://codeforces.com/contest/894/problem/A
 * Submit Date : 2025-08-31
 */



#include <iostream>

int main() {

  std::string s;
  std::cin >> s;
  long q(0), qa(0), qaq(0);
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == 'A') {
      qa += q;
    } else if (s[p] == 'Q') {
      ++q;
      qaq += qa;
    }
  }

  std::cout << qaq << std::endl;

  return 0;
}
