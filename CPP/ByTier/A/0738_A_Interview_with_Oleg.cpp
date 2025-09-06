/*
 * Problem URL : https://codeforces.com/contest/738/problem/A
 * Submit Date : 2025-09-04
 */

#include <iostream>
#include <string>
#include <regex>
int main(){
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::regex regex("ogo(go)*");
  std::cout << std::regex_replace(s, regex, "***") << std::endl;
  return 0;
}/*1698311768.7007358*/