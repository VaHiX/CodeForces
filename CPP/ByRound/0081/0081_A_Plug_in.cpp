/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <iostream>

int main() {

  std::string input;
  getline(std::cin, input);
  std::string output("");

  for (int k = 0; k < input.size(); k++) {
    if (output.empty() || output.back() != input[k]) {
      output += input[k];
    } else {
      output.pop_back();
    }
  }

  std::cout << output << std::endl;
  return 0;
}
