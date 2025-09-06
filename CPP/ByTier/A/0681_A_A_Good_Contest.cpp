/*
 * Problem URL : https://codeforces.com/contest/681/problem/A
 * Submit Date : 2025-09-02
 */



#include <iostream>

int main() {

  int n;
  std::cin >> n;
  std::string ans("NO");
  const int MIN = 2400;
  while (n--) {
    std::string name;
    std::cin >> name;
    int before, after;
    std::cin >> before >> after;
    if (before >= MIN && after > before) {
      ans = "YES";
      break;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
