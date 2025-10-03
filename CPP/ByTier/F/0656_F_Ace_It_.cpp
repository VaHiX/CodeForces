/*
 * Problem URL : https://codeforces.com/contest/656/problem/F
 * Submit Date : 2025-09-02
 */

#include <iostream>

int main() {

  std::string s;
  std::cin >> s;
  int count = 1;
  for (int p = 1; p < s.size(); p++) {
    count += (s[p] == '0') ? 9 : (s[p] - '0');
  }
  std::cout << count << std::endl;
}
