// Problem: CF 1662 E - Round Table
// https://codeforces.com/contest/1662/problem/E

/*
 * Problem: E. Round Table
 * Algorithm: Use Binary Indexed Tree (Fenwick Tree) to count inversions and compute minimum swaps.
 * 
 * Approach:
 * - The problem involves finding minimum swaps to reorder people around a circular table,
 *   where swapping adjacent people is allowed except between person x and x+1 (with wraparound).
 * - This can be reduced to counting inversions in a circular permutation using a Fenwick Tree.
 * - For each element in reversed order, we calculate how many elements are in the wrong place
 *   using BIT and accumulate the cost.
 *
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) for BIT and auxiliary arrays
 */

#include <stdio.h>
#include <iosfwd>

#define SIZE 200005
using namespace std;
typedef long long int ll;

// Binary Indexed Tree (Fenwick Tree) implementation
struct BIT {
  int bit[SIZE];
  int sz;
  void init(int n) {
    sz = n + 2;
    for (int i = 0; i < sz; i++)
      bit[i] = 0;
  }
  void add(int k, int x) {
    k++; // Convert to 1-based indexing
    while (k < sz) {
      bit[k] += x;
      k += k & -k; // Move to parent node
    }
  }
  int get(int k) {
    k++; // Convert to 1-based indexing
    int ret = 0;
    while (k > 0) {
      ret += bit[k];
      k -= k & -k; // Move to parent node
    }
    return ret;
  }
  int get(int s, int t) { return get(t) - get(s - 1); } // Range query
} bit;

int A[SIZE], pos[SIZE]; // A stores desired order, pos stores positions

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
    A[i]--; // Convert to 0-based indexing
    pos[A[i]] = i; // Store the index of each person in the desired arrangement
  }
  bit.init(n);
  ll ret = 0;
  // Process from last to first in the desired arrangement
  for (int i = n - 1; i >= 0; i--) {
    if (i + 1 < n) {
      int d = 0;
      // If the current person is to the left of the next person in the linear arrangement
      if (pos[i] < pos[i + 1]) {
        // Count elements between them using BIT
        d = bit.get(pos[i], pos[i + 1] - 1);
      } else {
        // Person i is to the right of person i+1, so count elements beyond i+1
        // but excluding those already placed
        d = (n - i - 1) - bit.get(pos[i + 1], pos[i]);
      }
      // Add the cost to total swaps. The cost is proportional to the index of current element.
      ret += (ll)d * (i + 1);
    }
    // Mark current person as processed
    bit.add(pos[i], 1);
  }
  printf("%lld\n", ret);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/