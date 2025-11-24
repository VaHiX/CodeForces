// Problem: CF 1983 D - Swap Dilemma
// https://codeforces.com/contest/1983/problem/D

/*
 * Problem: D. Swap Dilemma
 *
 * Purpose:
 *   Determine if two arrays can be made equal by performing a specific type of swap operation.
 *   Each operation allows swapping elements at positions [l,r] in array 'a' and [p,q] in array 'b',
 *   such that (r - l) == (q - p). This effectively allows swapping subarrays of equal length.
 *
 * Approach:
 *   This problem is based on the idea of parity of inversions. The key insight is that the operations
 *   described allow us to perform swaps of segments of equal lengths, but we are interested
 *   in whether we can make both arrays identical. The core idea is to compute a parity (odd/even)
 *   of inversions for each array. If these parities match, it's possible to make them equal.
 *
 *   To do this efficiently:
 *   - We use a Binary Indexed Tree (BIT) to maintain prefix counts of elements during traversal.
 *   - For each element, we count how many elements greater than it have already been seen.
 *   - We compute a parity (xor) of these counts for both arrays.
 *   - If the parities do not match, return "NO".
 *   - Also, check that all elements of 'b' exist in 'a' (and vice versa).
 *
 * Time Complexity:
 *   O(n log n) per test case due to BIT operations and loop over n elements.
 *
 * Space Complexity:
 *   O(N) where N = 2e5 + 5, for BIT and cnt arrays.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#ifdef Nero
#include "Deb.h"
#else
#define debug(...)
#endif
const int N = 2e5 + 5;
int cnt[N];         // Count of occurrences of each value
int tree[N];        // Binary Indexed Tree for efficient prefix queries

// Update BIT at position 'id' by adding value 'v'
inline void upd(int id, int v) {
  while (id < N) {
    tree[id] += v;
    id += id & -id;
  }
}

// Query sum from 1 to 'id'
inline int qry(int id) {
  int ret = 0;
  while (id) {
    ret += tree[id];
    id -= id & -id;
  }
  return ret;
}

// Query sum from 'l' to 'r'
int qry(int l, int r) { return qry(r) - qry(l - 1); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    bool ans = false;
    
    // Process array 'a' and compute parity
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      ans ^= qry(a[i] + 1, N - 1) % 2;  // XOR the parity of inversion count
      upd(a[i], 1);                     // Update BIT with current element
      cnt[a[i]]++;                      // Increment count of current element
    }
    
    // Reset BIT for second array processing
    for (int i = 0; i < n; ++i) {
      upd(a[i], -1);  // Remove elements of 'a' from BIT
    }
    
    bool ok = true;
    // Process array 'b' and check validity of mapping and parity
    for (int i = 0; i < n; ++i) {
      cin >> b[i];
      if (!cnt[b[i]]) {
        ok = false;  // Element in 'b' not present in 'a'
      } else {
        cnt[b[i]]--;  // Decrement count
      }
      ans ^= qry(b[i] + 1, N - 1) % 2;  // XOR the parity of inversion count for 'b'
      upd(b[i], 1);                    // Update BIT with current element of 'b'
    }
    
    // Reset cnt array
    for (int i = 0; i < n; ++i) {
      cnt[a[i]] = 0;
    }
    
    cout << (!ok || ans ? "NO" : "YES") << '\n';  // Output result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/