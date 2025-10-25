/*
 * Problem URL : https://codeforces.com/contest/258/problem/A
 * Submit Date : 2025-08-25
 */

#include <iostream>

int main() {

  std::string input;
  getline(std::cin, input);
  long found(input.size() - 1);
  for (int k = 0; k < input.size(); k++) {
    if (input[k] == '0') {
      found = k;
      break;
    }
  }
  std::cout << input.substr(0, found) + input.substr(found + 1) << std::endl;

  return 0;
}
