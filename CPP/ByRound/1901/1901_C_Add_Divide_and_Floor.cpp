// Problem: CF 1901 C - Add, Divide and Floor
// https://codeforces.com/contest/1901/problem/C

/*
 * Problem: C. Add, Divide and Floor
 * 
 * Algorithm:
 * - The core idea is to reduce all elements of the array to the same value using a specific operation.
 * - For each element a[i], we can perform an operation with x to replace it with floor((a[i] + x) / 2).
 * - The key insight is to simulate the process by using bit operations:
 *   - If the current minimum value 'min' is odd, we add 1 to it (x = 1).
 *   - Otherwise, x = 0.
 *   - Then we perform floor((min + x)/2) and floor((max + x)/2) for the new min and max.
 *   - Continue until min == max.
 * - The number of operations needed is equal to the number of steps required to bring the min and max to the same value.
 * 
 * Time Complexity: O(log(max_val)) where max_val is the maximum value in the array.
 * Space Complexity: O(log(max_val)) for storing the operations.
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

template <class _Tp = int> _Tp read() {
  static bool unsynced = false;
  if (!unsynced) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsynced = true;
  }
  _Tp ret = 0;
  char ch = std::cin.get(), sgn = false;
  while (!isdigit(ch))
    sgn |= ch == '-', ch = std::cin.get();
  while (isdigit(ch))
    ret = ret * 10 + ch - '0', ch = std::cin.get();
  return sgn ? -ret : ret;
}
const int kMaxN = 2e5 + 5;
int n;
int c[kMaxN];
int max_1, min_0;
bool get_f() {
  max_1 = 0, min_0 = 1e9;
  for (int i = 1; i <= n; i++)
    if (c[i] & 1)
      max_1 = std::max(max_1, c[i]);
    else
      min_0 = std::min(min_0, c[i]);
  return max_1 < min_0;
}
bool check_equal() {
  for (int i = 1; i <= n; i++)
    if (c[i] != c[1])
      return false;
  return true;
}
int opt[kMaxN];
int main() {
  int T = read();
  while (T--) {
    n = read();
    int min = 1e9, max = 0;
    for (int i = 1; i <= n; i++) {
      c[i] = read();
      min = std::min(min, c[i]);
      max = std::max(max, c[i]);
    }
    std::vector<int> opt;
    while (min != max) {
      int x = min & 1;        // Check if min is odd (x = 1) or even (x = 0)
      opt.push_back(x);       // Store the x value for this operation
      min = (min + x) / 2;    // Update min after operation
      max = (max + x) / 2;    // Update max after operation
    }
    printf("%d\n", opt.size()); // Print total number of operations
    if (opt.size() <= n) {
      for (auto i : opt)
        printf("%d ", i);     // Print the x values for each operation
      puts("");               // New line after printing x values
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/