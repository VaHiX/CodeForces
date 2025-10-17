/*
 * Problem URL : https://codeforces.com/contest/725/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>

int main() {

  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;

  long count(0);
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == '<') {
      ++count;
    } else {
      break;
    }
  }

  for (int p = s.size() - 1; p >= 0; p--) {
    if (s[p] == '>') {
      ++count;
    } else {
      break;
    }
  }

  std::cout << count << std::endl;

  return 0;
}
