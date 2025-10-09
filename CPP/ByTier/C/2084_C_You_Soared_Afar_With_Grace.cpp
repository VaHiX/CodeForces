// Problem: CF 2084 C - You Soared Afar With Grace
// https://codeforces.com/contest/2084/problem/C

/*
C. You Soared Afar With Grace

Problem Description:
Given two permutations a and b of length n, we can perform at most n swaps where each swap exchanges
elements at positions i and j in both arrays. The goal is to make array a equal to the reverse of array b,
i.e., for all i, a[i] should equal b[n+1-i].

Approach:
This problem can be solved by simulating the required swaps in a greedy manner:
- First, we check whether it's possible to make a and b reverse of each other.
- Then, greedily swap elements to align corresponding positions in reverse order.

Time Complexity: O(n) amortized per test case (due to operations being bounded by n)
Space Complexity: O(n) for the arrays and auxiliary structures

Algorithms/Techniques:
- Greedy swapping
- Two-pointer approach for checking reverse alignment
- Simulated swaps using index tracking

*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
const int N = 2e5 + 3;
int T, n, a[N], b[N], f, p[N], k;

// Function to perform a swap in both arrays and update index mapping p
void jh(int x, int y) {
  swap(p[a[x]], p[a[y]]);  // Update positions in the inverse mapping
  swap(a[x], a[y]);        // Swap elements in array a
  swap(b[x], b[y]);        // Swap elements in array b
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      p[a[i]] = i;  // Build index mapping from value to position
    }
    f = 0;
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
      if (a[i] == b[i])
        f++, k = i;  // Count matching elements and track one of them
    }

    // Check if the configuration allows reverse alignment
    for (int i = 1; i <= n; i++) {
      if (b[p[b[i]]] != a[i]) {
        f = 114514;  // Mark as invalid
        break;
      }
    }

    if (f != n % 2) {  // Check parity condition for valid solution
      cout << "-1\n";
      continue;
    }

    vector<pair<int, int>> s;  // Stores operations

    // Handle the case where an odd-length array has a center element matching itself
    if (f && k != n / 2 + 1) {
      s.push_back({k, n / 2 + 1});
      jh(k, n / 2 + 1);
    }

    // Perform swaps to align reverse pairs
    for (int i = 1; i <= n / 2; i++) {
      if (a[i] != b[n - i + 1]) {
        s.push_back({p[b[i]], n - i + 1});  // Record indices of required swap
        jh(p[b[i]], n - i + 1);            // Perform the actual swap
      }
    }

    cout << s.size() << '\n';
    for (auto i : s)
      cout << i.first << ' ' << i.second << '\n';
  }
}


// https://github.com/VaHiX/codeForces/