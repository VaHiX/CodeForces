// Problem: CF 1851 D - Prefix Permutation Sums
// https://codeforces.com/contest/1851/problem/D

/*
 * Problem: Prefix Permutation Sums
 * 
 * Purpose: Determine if a given array of prefix sums (with one element removed)
 *          corresponds to a valid permutation of integers from 1 to n.
 * 
 * Algorithm:
 * 1. For a valid permutation, we can compute the original array elements by
 *    taking differences of consecutive prefix sums.
 * 2. Any element in the original array must be between 1 and n.
 * 3. When we subtract adjacent prefix sums to get the original elements, we may
 *    find one element which is outside the [1,n] range; that's the missing element.
 * 4. If a valid permutation exists:
 *    - There will be exactly one element > n (the missing one),
 *    - And all elements in [1,n] except the missing one must occur once.
 * 5. We use a counting array to track which numbers in [1,n] appear in the original array.
 * 6. Then, we compare against the expected values.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for the counting array
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ull unsigned long long
#define int long long
#define x first
#define y second
#define pii pair<int, int>
#define ar array<int, 2>
#define inf 0x3f3f3f3f
#define endl '\n'
#define _                                                                      \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
const int N = 2e5 + 10, mod = 1e9 + 7;
const int seed = 13331;
int n;
int a[N];
int st[N];

void solve() {
  cin >> n;
  int num1 = -1; // Stores the value of the missing element (> n)
  vector<int> v; // Stores elements that are missing from [1, n]

  // Read prefix sums
  for (int i = 1; i < n; i++)
    cin >> a[i], st[i] = 0;
  st[n] = 0;

  // Calculate original elements and find those outside [1,n]
  for (int i = 1; i < n; i++) {
    int num = a[i] - a[i - 1]; // Difference gives original element
    if (num > n)
      num1 = num; // If greater than n, it is the missing element
    else
      st[num]++; // Count occurrences of elements in [1,n]
  }

  // Find elements from [1,n] that do not appear in the original array
  for (int i = 1; i <= n; i++) {
    if (!st[i])
      v.push_back(i);
  }

  // If there is no missing element (all elements were in [1,n])
  if (num1 == -1) {
    if (v.size() == 1) {
      if (st[v[0]] == 0)
        cout << "YES" << endl;
      else
        cout << "NO" << endl;
    } else if (v.size() == 2) {
      int kk = v[0] + v[1];
      if (st[kk] == 2)
        cout << "YES" << endl;
      else
        cout << "NO" << endl;
    } else
      cout << "NO" << endl;
    return;
  }

  // If there's a missing element, check if the sum of missing elements equals it
  if (v.size() == 2) {
    if (v[0] + v[1] == num1)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  } else
    cout << "NO" << endl;
}

signed main() {
  _ int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/