/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  const int N = 26;

  std::string source, target;
  getline(std::cin, source);
  getline(std::cin, target);

  std::vector<std::vector<long>> pos(N);
  for (size_t p = 0; p < source.size(); p++) {
    pos[source[p] - 'a'].push_back(p);
  }

  long count(1);
  long index = -1;
  for (size_t p = 0; p < target.size(); p++) {
    int letter = target[p] - 'a';
    if (pos[letter].empty()) {
      count = -1;
      break;
    }
    std::vector<long>::iterator posPointer =
        std::upper_bound(pos[letter].begin(), pos[letter].end(), index);
    if (posPointer == pos[letter].end()) {
      ++count;
      index = -1;
    }
    index = *std::upper_bound(pos[letter].begin(), pos[letter].end(), index);
  }

  std::cout << count << std::endl;

  return 0;
}
