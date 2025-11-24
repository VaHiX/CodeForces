// Problem: CF 1854 A1 - Dual (Easy Version)
// https://codeforces.com/contest/1854/problem/A1

/*
Algorithm: Dual (Easy Version)
Purpose: Transform an array into a non-decreasing sequence using at most 50 operations.
Techniques: 
- Use doubling strategy to make a positive element large enough to handle negative elements.
- Then add that large element to all negative elements.
- Finally, make the array non-decreasing by adding each element to the next one in order.

Time Complexity: O(n^2) per test case in worst case due to operations on array elements.
Space Complexity: O(n) for storing the operations and auxiliary array.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define nd second
#define st first
#define mp make_pair
#define pb push_back
#define orta (((bas) + (son)) / 2)
#define sol (k + k)
#define sag (k + k + 1)
const int N = 5e5 + 5;
const int M = 605;
const int inf = 1e9 + 5;
const ll linf = 1e18 + 5;
const int mod = 1e9 + 7;
const int logN = 17;
int n, m, k, x, y, z, t;
int a[30];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    vector<pii> ans;
    int pos = -1;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      if (a[i] > 0) {
        pos = i;
      }
    }
    if (pos != -1) {
      // Double the positive element until it's large enough to cover all negative numbers
      while (a[pos] <= 20) {
        ans.pb({pos, pos});
        a[pos] *= 2;
      }
      // Add this large value to all negative elements
      for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
          a[i] += a[pos];
          ans.pb({i, pos});
        }
      }
      // Ensure the array is non-decreasing by adding each element to the next one
      for (int i = 1; i < n; i++) {
        ans.push_back({i + 1, i});
      }
      printf("%d\n", ans.size());
      for (auto x : ans) {
        printf("%d %d\n", x.st, x.nd);
      }
    } else {
      // If no positive element exists, find the first negative element to use for doubling
      for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
          pos = i;
        }
      }
      if (pos == -1) {
        // All elements are non-negative, already sorted
        puts("0");
        continue;
      }
      // Double the negative element until it's small enough to be used for addition
      while (a[pos] >= -20) {
        ans.pb({pos, pos});
        a[pos] *= 2;
      }
      // Add it to the last element to help make array non-decreasing
      ans.pb({n, pos});
      // Process the array backwards to make it non-decreasing
      for (int i = n - 1; i >= 1; i--) {
        ans.pb({i, i + 1});
      }
      printf("%d\n", ans.size());
      for (auto x : ans) {
        printf("%d %d\n", x.st, x.nd);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/