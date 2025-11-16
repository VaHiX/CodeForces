// Problem: CF 1833 D - Flipper
// https://codeforces.com/contest/1833/problem/D

/*
 * Code Purpose: This code finds the lexicographically maximum permutation that can be obtained
 *               by performing exactly one operation on a given permutation. The operation involves
 *               choosing a segment [l, r], reversing it, and then swapping the prefix [1, l-1] and
 *               suffix [r+1, n].
 *
 * Algorithms/Techniques:
 * - Greedy approach to determine the optimal segment [l, r] to reverse.
 * - The logic is based on identifying where reversing a segment and swapping the prefix/suffix
 *   will yield the maximum lexicographical result.
 *
 * Time Complexity: O(n^2) in worst case due to nested loops for determining the optimal l and r.
 * Space Complexity: O(n) for storing the permutation array.
 */

#include <iostream>

using namespace std;
typedef long long ll;
ll T, n, a[2005];

// Function to perform the operation and print the resulting permutation
void action(ll l, ll r) {
  // Print suffix [r+1, n]
  for (ll i = r + 1; i <= n; i++) {
    cout << a[i] << " ";
  }
  // Print reversed segment [l, r]
  for (ll i = r; i >= l; i--) {
    cout << a[i] << " ";
  }
  // Print prefix [1, l-1]
  for (ll i = 1; i <= l - 1; i++) {
    cout << a[i] << " ";
  }
  cout << '\n';
}

// Main logic for each test case
void run() {
  cin >> n;
  ll maxi = 0, ma = 0;
  // Read input and track maximum element and its position (excluding first element)
  for (ll i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] > ma && i > 1) {
      ma = a[i];
      maxi = i;
    }
  }
  // Base case: if n == 1, just print it
  if (n == 1) {
    cout << 1 << '\n';
    return;
  }
  ll l, r;
  // Case where maximum element is at the end
  if (maxi == n) {
    l = n, r = n;
    // Find the leftmost valid position for l
    for (ll i = 1; i <= n - 2; i++) {
      if (a[1] > a[n - i]) {
        break;
      } else {
        l = n - i;
      }
    }
  } else {
    // Find segment [l, r] centered around the position before the maximum element
    r = maxi - 1, l = r;
    // Find the leftmost valid position for l
    for (ll i = 1; i <= r - 1; i++) {
      if (a[1] > a[r - i]) {
        break;
      } else {
        l = r - i;
      }
    }
  }
  // Execute the operation and print result
  action(l, r);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    run();
  }
}


// https://github.com/VaHiX/CodeForces/