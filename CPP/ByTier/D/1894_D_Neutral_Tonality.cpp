// Problem: CF 1894 D - Neutral Tonality
// https://codeforces.com/contest/1894/problem/D

/*
Code Purpose:
This code solves the problem of inserting elements from array b into array a such that the resulting array c has the minimum possible LIS (Longest Increasing Subsequence) length.
The strategy is to use a greedy approach:
1. Sort array b in descending order.
2. Use two pointers to merge a and b into c:
   - When b[j] >= a[i], insert b[j] first (to potentially break increasing sequences)
   - Otherwise, insert a[i] first
3. This minimizes the LIS by strategically inserting elements to avoid creating long increasing subsequences.

Algorithms/Techniques:
- Greedy algorithm with two pointers
- Sorting (descending order for b)
- Merging two sorted sequences

Time Complexity: O(n * log(n) + m * log(m) + n + m) 
Space Complexity: O(n + m)
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define pb push_back
#define all(x) x.begin(), (x).end()
#define rall(x) x.rbegin(), (x).rend()
void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(m), c;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < m; i++)
    cin >> b[i];
  sort(rall(b)); // Sort b in descending order to maximize chance of breaking LIS
  c.reserve(n + m);
  int i = 0, j = 0;
  while (i < n && j < m) {
    if (b[j] >= a[i]) {
      // Insert b[j] first if it's >= a[i], which helps minimize LIS
      c.pb(b[j]);
      j++;
    } else {
      // Insert a[i] first, as it's larger and won't extend the LIS as much
      c.pb(a[i]);
      i++;
    }
  }
  // Add remaining elements from a
  while (i < n)
    c.pb(a[i++]);
  // Add remaining elements from b
  while (j < m)
    c.pb(b[j++]);
  for (int x : c)
    cout << x << ' ';
  cout << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/