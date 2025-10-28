// Problem: CF 1157 C1 - Increasing Subsequence (easy version)
// https://codeforces.com/contest/1157/problem/C1

/*
 * Problem: C1. Increasing Subsequence (easy version)
 * Algorithm: Greedy approach to build the longest strictly increasing subsequence
 * by choosing elements from either left or right end of the array.
 *
 * Time Complexity: O(n) - Each element is visited at most once.
 * Space Complexity: O(n) - For storing the input vector and result string.
 */
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n); // Input array
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read elements into the array
  }
  long left(0), right(n - 1), cur(0); // Pointers and current value tracker
  std::vector<char> res; // Stores the result moves ('L' or 'R')
  // Decide initial move based on which end has smaller value
  if (a[0] < a.back()) {
    res.push_back('L');
    cur = a[0];
    left = 1;
  } else {
    res.push_back('R');
    cur = a.back();
    right = n - 2;
  }
  // Continue making moves while there are elements left
  while (left <= right) {
    // If both ends are valid for extension, prefer the one with smaller value
    if (cur < a[left] && a[left] < a[right]) {
      res.push_back('L');
      cur = a[left];
      ++left;
    } else if (cur < a[right] && a[right] <= a[left]) {
      res.push_back('R');
      cur = a[right];
      --right;
    } else if (cur < a[left]) {
      res.push_back('L');
      cur = a[left];
      ++left;
    } else if (cur < a[right]) {
      res.push_back('R');
      cur = a[right];
      --right;
    } else {
      break; // No valid move possible
    }
  }
  printf("%ld\n", res.size()); // Print length of the sequence
  for (long p = 0; p < res.size(); p++) {
    printf("%c", res[p]); // Print the moves
  }
  puts(""); // Newline after output
  return 0;
}


// https://github.com/VaHiX/codeForces/