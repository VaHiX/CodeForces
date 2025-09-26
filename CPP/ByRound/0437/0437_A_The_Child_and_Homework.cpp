/*
 * Problem URL : https://codeforces.com/problemset/problem/437/A
 * Submit Date : 2025-08-19
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

int main() {

  const int N = 4;

  std::vector<int> lengthVec(N);
  for (int k = 0; k < N; k++) {
    std::string temp;
    getline(std::cin, temp);
    lengthVec[k] = temp.size() - 2;
  }

  int found = -1;
  for (int p = 0; p < N; p++) {
    if (lengthVec[p] >= 2 * lengthVec[(p + 1) % N] &&
        lengthVec[p] >= 2 * lengthVec[(p + 2) % N] &&
        lengthVec[p] >= 2 * lengthVec[(p + 3) % N]) {
      if (found < 0) {
        found = p;
      } else {
        found = 2;
        break;
      }
    }
    if (2 * lengthVec[p] <= lengthVec[(p + 1) % N] &&
        2 * lengthVec[p] <= lengthVec[(p + 2) % N] &&
        2 * lengthVec[p] <= lengthVec[(p + 3) % N]) {
      if (found < 0) {
        found = p;
      } else {
        found = 2;
        break;
      }
    }
  }

  if (found < 0) {
    found = 2;
  }

  printf("%c\n", 'A' + found);

  return 0;
}
