/*
 * Problem URL : https://codeforces.com/contest/776/problem/A
 * Submit Date : 2025-09-01
 */



#include <iostream>
#include <set>

int main() {

  std::set<std::string> a;
  std::string x, y;
  std::cin >> x >> y;
  a.insert(x);
  a.insert(y);
  std::cout << (*a.begin()) << " " << (*(++a.begin())) << std::endl;

  int n;
  std::cin >> n;
  while (n--) {
    std::cin >> x >> y;
    a.erase(x);
    a.insert(y);
    std::cout << (*a.begin()) << " " << (*(++a.begin())) << std::endl;
  }

  return 0;
}
