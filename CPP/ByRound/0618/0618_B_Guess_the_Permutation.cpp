/*
 * Problem URL : https://codeforces.com/contest/618/problem/B
 * Submit Date : 2025-09-10
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  int n;
  std::cin >> n;
  std::vector<int> perm(n, 0);
  for (int row = 0; row < n; row++) {
    int current(0);
    for (int col = 0; col < n; col++) {
      int x;
      std::cin >> x;
      current = std::max(current, x);
    }
    perm[row] = current;
  }

  for (int p = 0; p < n; p++) {
    if (perm[p] == n - 1) {
      perm[p] = n;
      break;
    }
  }
  for (int p = 0; p < n; p++) {
    std::cout << perm[p] << " ";
  };
  std::cout << std::endl;

  return 0;
}
