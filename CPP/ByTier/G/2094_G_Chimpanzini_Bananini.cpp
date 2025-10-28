// Problem: CF 2094 G - Chimpanzini Bananini
// https://codeforces.com/contest/2094/problem/G

/*
G. Chimpanzini Bananini
Algorithms/Techniques: Double-ended queue (deque) simulation with optimized rizziness calculation
Time Complexity: O(q) amortized per test case
Space Complexity: O(q) for the deque storage and auxiliary arrays

This code simulates operations on an array where each operation modifies the array,
and we need to calculate the "rizziness" of the array after each operation.
Rizziness is defined as sum of a[i] * i (1-indexed) over all elements.

The implementation uses two deques to simulate the current array and its reverse,
and maintains precomputed values to efficiently update rizziness without recalculating
from scratch each time.

Key Optimizations:
- Maintains running sum 's' of elements in current deque
- Tracks rizziness values for both deques using ans[0] and ans[1]
- Uses bit manipulation (cnt ^= 1) to toggle between deques
- Efficiently updates rizziness during cyclic shifts and reversals
*/

#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
#define int long long
int t, q;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> q;
    int op, x, cnt = 0, ans[2] = {0}, s = 0;
    deque<int> d[2]; // Two deques to maintain current array and its reverse
    while (q--) {
      cin >> op;
      if (op == 1) {
        // Cyclic shift operation: move last element to front
        int si = d[cnt].size(), tmp = d[cnt].back(); // Get size and last element
        d[cnt].pop_back(); // Remove from back
        d[cnt].push_front(tmp); // Add to front
        ans[cnt] += s - 1ll * si * tmp; // Update rizziness for current deque
        d[cnt ^ 1].pop_front(); // Remove from front of reverse deque
        d[cnt ^ 1].push_back(tmp); // Add to back of reverse deque
        ans[cnt ^ 1] += 1ll * si * tmp - s; // Update rizziness for reverse deque
      }
      if (op == 2)
        cnt ^= 1; // Toggle between deques (reverse operation)
      if (op == 3) {
        // Append element to the back of current deque
        cin >> x;
        d[cnt].push_back(x); // Add to back of current deque
        s += x; // Update running sum
        ans[cnt] += 1ll * d[cnt].size() * x; // Update rizziness for current deque
        d[cnt ^ 1].push_front(x); // Add to front of reverse deque
        ans[cnt ^ 1] += s; // Update rizziness for reverse deque
      }
      cout << ans[cnt] << "\n"; // Output rizziness of current deque
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/