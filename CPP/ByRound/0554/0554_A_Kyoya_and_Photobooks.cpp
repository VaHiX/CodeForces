/*
 * Problem URL : https://codeforces.com/contest/554/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/554/problem/A
 * Submit Date : 2025-09-02
 */



#include <iostream>

int main() {

  const int N = 26;
  std::string s;
  getline(std::cin, s);
  long n = s.size();
  long ans = N + (N - 1) * n;
  std::cout << ans << std::endl;

  return 0;
}
