/*
 * Problem URL : https://codeforces.com/problemset/problem/474/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>
#include <iostream>

int main() {

  std::string upper = "qwertyuiop";
  std::string middle = "asdfghjkl;";
  std::string lower = "zxcvbnm,./";

  std::string direction;
  getline(std::cin, direction);
  std::string input;
  getline(std::cin, input);

  int dirNum = (direction[0] == 'R') ? (-1) : 1;
  int pos(0);

  for (int p = 0; p < input.size(); p++) {

    pos = upper.find(input[p]);
    if (pos != std::string::npos) {
      printf("%c", upper[pos + dirNum]);
    }
    pos = middle.find(input[p]);
    if (pos != std::string::npos) {
      printf("%c", middle[pos + dirNum]);
    }
    pos = lower.find(input[p]);
    if (pos != std::string::npos) {
      printf("%c", lower[pos + dirNum]);
    }
  }

  puts("");

  return 0;
}
