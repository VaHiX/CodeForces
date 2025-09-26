/*
 * Problem URL : https://codeforces.com/contest/343/problem/B
 * Submit Date : 2025-09-09
 */

/*
 * Problem URL : https://codeforces.com/contest/343/problem/B
 * Submit Date : 2025-09-08
 */

#include <cstdio>
#include <iostream>
#include <vector>

int main() {

  std::string input;
  getline(std::cin, input);
  std::vector<char> state;
  for (long p = 0; p < input.size(); p++) {
    if (!state.empty() && state.back() == input[p]) {
      state.pop_back();
    } else {
      state.push_back(input[p]);
    }
  }

  puts(state.empty() ? "Yes" : "No");

  return 0;
}
