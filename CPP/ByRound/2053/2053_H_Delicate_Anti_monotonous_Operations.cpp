// Problem: CF 2053 H - Delicate Anti-monotonous Operations
// https://codeforces.com/contest/2053/problem/H

/*
 * Problem: H. Delicate Anti-monotonous Operations
 * Algorithms/Techniques: Simulation, Greedy, Two Pointers, Prefix Sum
 *
 * Time Complexity: O(n) per test case (amortized)
 * Space Complexity: O(1) additional space (excluding input array)
 *
 * Description:
 * Iris has an integer sequence of length n, each number in the range [1,w].
 * She can perform operations: select two adjacent equal elements a[i] = a[i+1],
 * and transform them to any values in [1,w], such that after operation a[i] != a[i+1].
 * Goal:
 *   Maximize the final sum of sequence.
 *   Minimize number of operations to reach this sum.
 *
 * Approach:
 * - If array already has no adjacent equal elements, answer is just sum and 0 operations.
 * - If any element in the array equals w, we can make all elements w (to maximize total).
 *   Then, we compute how many moves are needed.
 * - Otherwise, use greedy to try to avoid creating long consecutive sequences.
 * - For cases where we must break chains of repeated values:
 *   - Try different starting/ending points and simulate operation costs.
 *   - Reverse the subarray and see if it reduces operation count.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <numeric>

#define int long long
using namespace std;

inline int read() {
  int s = 0, w = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      w = -1;
    ch = getchar();
  }
  while (ch <= '9' && ch >= '0')
    s = s * 10 + ch - '0', ch = getchar();
  return s * w;
}

int n, w, arr[200005];

// Calculates minimal operations to "break" a group of consecutive elements
int calculate_operations(int length) {
  if (length == 0)
    return 0;
  if (length == 1)
    return 2;
  return (length + 1) / 2;
}

// Finds minimum cost for subarray from left to right
int find_min_operations(int left, int right) {
  int consecutive_count = 0, operation_count = 0, min_operations = 1e18;
  for (int i = left; i < right; i++) {
    if (arr[i + 1] == arr[i]) {
      // Early termination condition: when current pair is equal
      min_operations =
          min(min_operations, operation_count + (right - i) + right - left - 1 -
                                  (consecutive_count == 1 && i + 2 <= right &&
                                   arr[i + 2] != w));
    }
    if (arr[i] == w) {
      operation_count -= calculate_operations(consecutive_count);
      consecutive_count++;
      operation_count += calculate_operations(consecutive_count);
    } else {
      consecutive_count = 0;
    }
  }
  return min_operations;
}

void solve(int test_case) {
  cin >> n >> w;
  for (int i = 1; i <= n; i++)
    cin >> arr[i];

  if (*min_element(arr + 1, arr + 1 + n) == w) {
    cout << n * w << " 0\n";
    return;
  }
  if (n == 1) {
    cout << arr[1] << " 0\n";
    return;
  }

  if (w == 2) {
    int max_sum = 2 * n, operations = 0;
    for (int i = 1; i <= n; i++)
      if (arr[i] == 1) {
        int left = i;
        while (left + 1 <= n && arr[left + 1] == arr[i])
          left++;
        max_sum--;
        operations += left - i;
        i = left;
      }
    cout << max_sum << " " << operations << "\n";
    return;
  }

  bool has_equal_adjacent = false;
  for (int i = 1; i < n; i++)
    if (arr[i] == arr[i + 1])
      has_equal_adjacent = true;
  if (!has_equal_adjacent) {
    cout << accumulate(arr + 1, arr + 1 + n, 0ll) << " 0\n";
    return;
  }
  cout << n * w - 1 << " ";
  if (accumulate(arr + 1, arr + 1 + n, 0ll) == n * w - 1) {
    cout << "0\n";
    return;
  }
  int left = (arr[1] == w ? 2 : 1), right = (arr[n] == w ? n - 1 : n);
  int min_operations = 1e18;
  if ((arr[n - 1] == w && arr[n] == w) || (arr[1] == w && arr[2] == w)) {
    while (arr[left] == w)
      left++;
    while (arr[right] == w)
      right--;
    int operations = right - left + 2;
    for (int i = left; i <= right; i++)
      if (arr[i] == w) {
        int x = i;
        while (x + 1 <= right && arr[x + 1] == w)
          x++;
        operations += calculate_operations(x - i + 1);
        i = x;
      }
    min_operations = operations;
  }
  min_operations = min(min_operations, find_min_operations(left, right));
  reverse(arr + left, arr + right + 1);
  min_operations = min(min_operations, find_min_operations(left, right));
  cout << min_operations << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int test_cases;
  cin >> test_cases;
  for (int i = 1; i <= test_cases; i++)
    solve(i);
  return 0;
}


// https://github.com/VaHiX/codeForces/