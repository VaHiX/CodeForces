// Problem: CF 1689 E - ANDfinity
// https://codeforces.com/contest/1689/problem/E

/*
 * Problem: E. ANDfinity
 * Purpose: Given an array of non-negative integers, determine the minimum number of operations
 *          (increment/decrement) to make the graph connected where vertices are connected if 
 *          their bitwise AND is greater than 0.
 * 
 * Algorithm:
 * - For each array element, check if we can make the graph connected with minimum operations.
 * - The key optimization is to use bit manipulation to understand which bits are set in each number,
 *   and how they interact to form connections.
 * - Try to reduce the number of operations by incrementing or decrementing values.
 * - Use a check function (`chk`) to verify if the current graph is connected based on bitwise ANDs.
 *
 * Time Complexity: O(n^2 * 30) for each test case, roughly O(n^2) in practice due to bit operations.
 * Space Complexity: O(1) - only using a fixed-size array.
 */

#include <iostream>

using namespace std;
typedef long long ll;
int i, j, k, n, m, t, res, a[10050], sb, mx;
#define b(x) (1 << ((x) - 1))  // Helper macro to compute 2^(x-1)

// Function to check if the current graph is connected.
// It does a bitwise union operation through all bits and verifies coverage.
bool chk() {
  int i, j, k, f[33] = {0}, cur = 0;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= 30; j++)
      if (a[i] & b(j)) {
        f[j] |= a[i];  // Store all bits that are set in a[i] and their corresponding values
        cur = f[j];
      }
  for (i = 1; i <= 30; i++)
    for (j = 1; j <= 30; j++)
      if (cur & f[j])
        cur |= f[j];  // Union all reachable bits from current set
  for (i = 1; i <= 30; i++)
    if ((cur & f[i]) != f[i])
      return 0;  // If coverage is incomplete, graph is not connected
  return 1;
}

// Print result
void show() {
  cout << res << '\n';
  for (int i = 1; i <= n; i++)
    cout << a[i] << ' ';
  cout << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    mx = res = 0;
    for (i = 1; i <= n; i++) {
      cin >> a[i];
      if (!a[i]) {  // If element is 0, we must increment it
        res++;
        a[i]++;
        continue;
      }
      sb = (-a[i] & a[i]);  // Find the rightmost set bit
      if (sb > mx)  // Track the maximum of such bits
        mx = sb;
    }
    if (chk())  // Check if already connected
      goto aaa;
    res++;
    for (i = 1; i <= n; i++) {
      if (a[i] == 1)  // Special handling for 1 - if it can be decremented to 0, skip
        goto aa;
      a[i]--;  // Try decrementing
      if (chk()) {
        goto aaa;
      }
      a[i]++;  // Revert if not successful
    aa:;
      a[i]++;  // Try incrementing
      if (chk()) {
        goto aaa;
      }
      a[i]--;  // Revert if not successful
    }
    res++;
    // Try to modify elements with maximum rightmost bit
    for (i = 1; i <= n; i++)
      if ((-a[i] & a[i]) == mx) {  // If the rightmost set bit matches mx
        a[i]--;  // Decrement one such element
        break;
      }
    for (i = 1; i <= n; i++)
      if ((-a[i] & a[i]) == mx) {  // And increment another element with same bit
        a[i]++;
        break;
      }
  aaa:;
    show();  // Print final result
  }
}


// https://github.com/VaHiX/CodeForces/