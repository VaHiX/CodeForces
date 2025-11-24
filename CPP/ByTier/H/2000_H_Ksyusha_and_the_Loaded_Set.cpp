// Problem: CF 2000 H - Ksyusha and the Loaded Set
// https://codeforces.com/contest/2000/problem/H

/*
H. Ksyusha and the Loaded Set
Algorithms/Techniques: Segment Tree with Lazy Propagation, Set for maintaining sorted elements

Time Complexity:
  - Initialization: O(n * log n)
  - Each operation:
    - Insert/Remove: O(log n)
    - Query: O(log n)
  - Overall: O((n + m) * log n) per test case

Space Complexity:
  - O(n) for set + O(2 * 2^Log) for segment tree = O(n + 2^Log)
*/

#include <algorithm>
#include <iostream>
#include <set>

using namespace std;
const int maxn = 2e6, Log = 21, pot = (1 << Log);
const int inf = 1e9;

struct tournament {
  int t[pot * 2]; // Segment tree to store maximum gap sizes
  void update(int x, int val) {
    t[x] = val;
    for (x /= 2; x; x /= 2) { // Update parents in segment tree
      t[x] = max(t[x * 2], t[x * 2 + 1]);
    }
  }
  int query(int val) {
    int x = 1;
    while (x < pot) {
      if (t[x * 2] >= val) { // If left child has sufficient value, go left
        x *= 2;
      } else {
        x = x * 2 + 1; // Else go right
      }
    }
    return x - pot; // Return original index in the array
  }
};

set<int> s; // Set to maintain sorted order of elements
tournament T;

void solve() {
  int n;
  cin >> n;
  int a;
  int prosl = 0; // previous element, used to calculate gaps
  s.insert(0); // Insert dummy element at beginning for easier gap calculation
  for (int i = 0; i < n; i++) {
    cin >> a;
    s.insert(a);
    T.update(prosl + 1 + pot, a - prosl - 1); // Update the segment tree with gap size
    prosl = a;
  }
  s.insert(inf); // Insert dummy element at end for easier gap calculation
  T.update(prosl + 1 + pot, inf - prosl - 1);
  int m;
  cin >> m;
  char c;
  int x;
  for (int i = 0; i < m; i++) {
    cin >> c >> x;
    if (c == '-') { // Remove element
      auto it = s.lower_bound(x); // Find the element to delete
      T.update(x + 1 + pot, 0); // Update segment tree: element deleted, so gap at this point is zero
      it = s.erase(it);
      x = *it; // Get next element
      it--; // Go back to previous element
      T.update(*it + 1 + pot, x - *it - 1); // Update the gap before the erased element
    } else if (c == '+') { // Insert element
      auto it = s.lower_bound(x);
      T.update(x + 1 + pot, *it - x - 1); // Update the new gap after inserted element
      it--;
      T.update(*it + 1 + pot, x - *it - 1); // Update the gap before inserted element
      s.insert(x);
    } else { // Query for k-load
      cout << T.query(x) << ' '; // Use segment tree to find first gap of size at least x
    }
  }
  cout << '\n';
  while (!s.empty()) {
    if (s.size() > 1) {
      T.update(*s.begin() + 1 + pot, 0); // Clear the tree from the set when done
    }
    s.erase(s.begin());
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/