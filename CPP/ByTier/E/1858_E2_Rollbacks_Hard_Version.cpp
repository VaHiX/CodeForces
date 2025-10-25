// Problem: CF 1858 E2 - Rollbacks (Hard Version)
// https://codeforces.com/contest/1858/problem/E2

/*
 * Problem: E2. Rollbacks (Hard Version)
 * Purpose: Process a series of operations on an array, including adding elements,
 *          removing the last k elements, rolling back changes, and querying the
 *          number of distinct elements in the array.
 *
 * Algorithm:
 * - Maintain the array using a stack to track changes for rollback.
 * - For each addition, track the position in the array and update distinct count.
 * - For each deletion, record how many elements were removed.
 * - For rollback, revert the most recent change from the stack.
 * - Query returns the number of distinct elements at the current state.
 *
 * Time Complexity: O(q) where q is the number of queries, assuming amortized operations.
 * Space Complexity: O(n) where n is the maximum size of the array during operations.
 */

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

const int N = 1e6 + 5;
int q, a[N], m, n, pos[N], fir[N], dif[N];

// Structure to hold state changes for rollback
struct Ver {
  int ty, a, b, c, d;
};

stack<Ver> st;

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> q;

  while (q--) {
    char ty;
    cin >> ty;

    if (ty == '+') {
      // Add element to the array
      m++; // Increment array index
      n++; // Increment current size
      cin >> a[m]; // Read the value to add
      // Push the state before modification to the stack for rollback
      st.push({0, a[m], pos[n], fir[a[pos[n]]], fir[a[m]]});
      // Update tracking of the last occurrence of the element that was at pos[n]
      if (fir[a[pos[n]]] == n)
        fir[a[pos[n]]] = 0;
      pos[n] = m; // Update position of current element
      dif[m] = dif[pos[n - 1]]; // Copy previous distinct count
      // If this value has not been seen or is seen later than current, update
      if (!fir[a[m]] || fir[a[m]] > n) {
        fir[a[m]] = n;
        dif[m]++;
      }
    }

    if (ty == '-') {
      // Remove last k elements
      int k;
      cin >> k;
      st.push({1, k, 0, 0, 0}); // Push rollback info for deletion
      n -= k; // Reduce the current size
    }

    if (ty == '!') {
      // Rollback the last operation
      auto x = st.top();
      st.pop();
      if (x.ty) {
        // Rolling back a deletion
        n += x.a;
      } else {
        // Rolling back an addition
        a[m] = x.a;
        pos[n] = x.b;
        fir[a[pos[n]]] = x.c;
        fir[a[m]] = x.d;
        m--;
        n--;
      }
    }

    if (ty == '?') {
      // Query distinct count
      cout << dif[pos[n]] << endl; // Output the count of distinct elements
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/