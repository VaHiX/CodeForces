/*
 * Problem URL : https://codeforces.com/contest/844/problem/A
 * Submit Date : 2025-08-31
 */

#include <iostream>
#include <set>

int main() {

  const int N = 26;
  std::string s;
  std::cin >> s;
  int k;
  std::cin >> k;
  std::set<char> t;
  for (int p = 0; p < s.size(); p++) {
    t.insert(s[p]);
  }
  if (k > s.size() || k > N) {
    std::cout << "impossible" << std::endl;
  } else {
    std::cout << ((k > t.size()) ? (k - t.size()) : 0) << std::endl;
  }

  return 0;
}
