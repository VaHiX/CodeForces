/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>
#include <iostream>
#include <set>
#include <string>

int main() {

  int n;
  std::cin >> n;
  std::set<std::pair<std::string, std::string>> leaves;
  while (n--) {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    leaves.insert(std::pair<std::string, std::string>(s1, s2));
  }

  std::cout << leaves.size() << std::endl;

  return 0;
}
