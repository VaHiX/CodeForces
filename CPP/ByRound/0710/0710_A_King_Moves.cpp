/*
 * Problem URL : https://codeforces.com/contest/710/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>
#include <iostream>

int main() {

  std::string s;
  std::cin >> s;
  bool hor = (s[0] == 'a') || (s[0] == 'h');
  bool ver = (s[1] == '1') || (s[1] == '8');
  if (hor && ver) {
    puts("3");
  } else if (hor || ver) {
    puts("5");
  } else {
    puts("8");
  }

  return 0;
}
