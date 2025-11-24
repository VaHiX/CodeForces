// Problem: CF 634 A - Island Puzzle
// https://codeforces.com/contest/634/problem/A

/*
 * Problem: Island Puzzle
 * 
 * Purpose: Determine if a sequence of statue moves on a circular island chain can transform
 *          the current statue configuration into a target configuration.
 * 
 * Algorithm: 
 *   1. Extract non-zero statues from both start and target arrays to form lists of statues.
 *   2. Identify the index in target where the first statue of start appears.
 *   3. Check if the start statue list matches the target list in a circular fashion.
 * 
 * Time Complexity: O(n), where n is the number of islands. We traverse the lists a constant number of times.
 * Space Complexity: O(n), to store the start and target statue lists.
 */
#include <cstdio>
#include <iostream>
#include <vector>
int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<long> start;
  for (int p = 0; p < n; p++) {
    long x;
    std::cin >> x;
    if (x == 0) {
      continue;
    }
    start.push_back(x);
  }
  std::vector<long> target;
  long ind(0);  // Index in target where the first statue of start occurs
  for (int p = 0; p < n; p++) {
    long x;
    std::cin >> x;
    if (x == 0) {
      continue;
    }
    target.push_back(x);
    if (x == start[0]) {
      ind = target.size() - 1;
    }
  }
  bool possible(true);
  for (int p = 0; p < n - 1; p++) {
    if (start[p] != target[(p + ind) % (n - 1)]) {
      possible = false;
      break;
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/