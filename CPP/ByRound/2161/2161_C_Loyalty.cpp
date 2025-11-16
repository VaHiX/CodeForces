// Problem: CF 2161 C - Loyalty
// https://codeforces.com/contest/2161/problem/C

/*
Purpose: This code solves the "Loyalty" problem where a customer wants to maximize bonus points by optimally ordering purchases.
         Bonus points are earned when buying items causes the loyalty level to increase (i.e., when the total cost crosses a multiple of X).

Algorithms/Techniques:
- Greedy approach with sorting: Items are sorted first to enable optimal selection strategy.
- Two-pointer technique: Used to process items from both ends of the sorted array to maximize bonuses.
- Priority-based selection: When adding an item, we check if including it causes a loyalty level increase, and if so, it contributes bonus points.

Time Complexity: O(n * log n) due to sorting, where n is the number of items.
Space Complexity: O(n) for storing the array and result vector.

*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define F first
#define S second
#define en end()
#define bg begin()
#define rev reverse
#define mp make_pair
#define pb push_back
const int N = 2e5 + 5;
const int inf = 1e9;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    cin >> n >> x;
    int a[n + 1];
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1); // Sort items in ascending order to facilitate greedy selection
    vector<int> v;
    ll b = 0; // Tracks the current loyalty level component (remainder)
    ll sum = 0; // Total bonus points
    int l = 1; // Left pointer (start of sorted array)
    int r = n; // Right pointer (end of sorted array)
    while (l <= r) {
      if (b + a[r] >= x) {
        // If adding the largest remaining item would increase the loyalty level,
        // then it's a bonus point item, so add its value to sum
        sum += a[r];
        b = b + a[r] - x; // Update the loyalty level component
        v.pb(a[r]); // Add to purchase order
        r--; // Move right pointer
      } else {
        // Otherwise, just add item to current sum
        b += a[l]; // Add the small item to the loyalty level
        v.pb(a[l]); // Add to purchase order
        l++; // Move left pointer
      }
    }
    cout << sum << endl;
    for (auto c : v)
      cout << c << ' ';
  }
}


// https://github.com/VaHiX/CodeForces/