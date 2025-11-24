// Problem: CF 1768 D - Lucky Permutation
// https://codeforces.com/contest/1768/problem/D

/*
 * Purpose: This code solves the "Lucky Permutation" problem where we need to find the minimum number of swaps
 *          to make the permutation have exactly one inversion.
 *
 * Algorithm: 
 * 1. First, we compute the cycle decomposition of the permutation.
 *    A cycle is a sequence of elements that forms a loop under the permutation.
 *    We mark each element with its cycle identifier.
 * 2. Then, we check if consecutive elements (in the original permutation) belong to the same cycle.
 *    If they do, it contributes to reducing the number of operations needed.
 * 3. The formula used is: n - c + d, where:
 *    - n is the length of the permutation
 *    - c is the number of cycles
 *    - d is -1 if there's at least one adjacent pair in the same cycle, otherwise 0
 *
 * Time Complexity: O(n) - Each element is visited once during cycle detection.
 * Space Complexity: O(n) - For storing the permutation and cycle tracking array.
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<int> p(n + 1), q(n + 1);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &p[i]);
    }
    int c = 0;
    for (int i = 1; i <= n; ++i) {
      if (q[i] == 0) {
        int j = i;
        do {
          q[j] = i;  // Mark the cycle identifier for node j
          j = p[j];  // Move to the next node in the cycle
        } while (j != i);  // Continue until we return to the start
        ++c;  // Count the cycle
      }
    }
    int d = 1;
    for (int i = 1; i < n; ++i) {
      if (q[i] == q[i + 1])  // Check if adjacent elements are in the same cycle
        d = -1;  // If so, we can reduce operations
    }
    printf("%d\n", n - c + d);  // Output the result using derived formula
  }
}


// https://github.com/VaHiX/CodeForces/