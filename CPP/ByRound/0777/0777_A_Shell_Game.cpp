/*
 * Problem URL : https://codeforces.com/contest/777/problem/A
 * Submit Date : 2025-09-01
 */

#include <iostream>
#include <vector>

int main() {

  const long N = 6;
  std::vector<std::string> a;
  a.push_back("012");
  a.push_back("102");
  a.push_back("120");
  a.push_back("210");
  a.push_back("201");
  a.push_back("021");

  long n, f;
  std::cin >> n >> f;
  int res = a[n % N][f] - '0';
  std::cout << res << std::endl;

  return 0;
}
