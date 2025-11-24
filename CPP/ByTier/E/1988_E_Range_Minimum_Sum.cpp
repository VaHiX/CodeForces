// Problem: CF 1988 E - Range Minimum Sum
// https://codeforces.com/contest/1988/problem/E

/*
 * Problem: E. Range Minimum Sum
 * 
 * Purpose: Given a permutation of integers, for each element in the permutation,
 *          calculate the sum of minimum elements over all subarrays after removing
 *          that element.
 * 
 * Algorithm:
 * - Use monotonic stack to find the left and right boundaries for each element
 *   such that the element is the minimum in that range.
 * - Precompute the total contribution of each element to the sum of all subarrays.
 * - For each element, calculate how much its removal affects the sum using
 *   precomputed deltas and adjustments.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) per test case
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forsn(i, s, n) for (int i = int(s); i < int(n); i++)
#define dforn(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define dforsn(i, s, n) for (int i = int(n) - 1; i >= int(s); i--)
#define fst first
#define snd second
#define pb push_back
#define eb emplace_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef pair<int, int> ii;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  forn(_, t) {
    int n;
    cin >> n;
    vi a(n);
    forn(i, n) cin >> a[i];
    vi l(n), r(n);
    // Compute left boundary for each element using monotonic stack
    forn(i, n) {
      int j = i - 1;
      while (j >= 0 && a[j] >= a[i])
        j = l[j];
      l[i] = j;
    }
    // Compute right boundary for each element using monotonic stack
    dforn(i, n) {
      int j = i + 1;
      while (j < n && a[j] > a[i])
        j = r[j];
      r[i] = j;
    }
    ll tot = 0;
    vll delta(n + 1, 0LL);
    // Precompute the total contribution of each element and delta values
    forn(i, n) {
      tot += 1LL * (r[i] - i) * (i - l[i]) * a[i];
      delta[i] += 1LL * (i - l[i]) * a[i];
      delta[r[i]] -= 1LL * (i - l[i]) * a[i];
      delta[l[i] + 1] += 1LL * (r[i] - i) * a[i];
      delta[i + 1] -= 1LL * (r[i] - i) * a[i];
    }
    // Build prefix sum of delta
    forn(i, n) delta[i + 1] += delta[i];
    forn(i, n) delta[i] -= a[i];
    forn(i, n) {
      int left = i - 1, right = i + 1;
      ll curr = tot - 1LL * (r[i] - right) * (left - l[i]) * a[i] - delta[i];
      // Adjust the result by traversing the updated boundaries
      while (left != l[i] || right != r[i]) {
        if (left != l[i] && (right == r[i] || a[left] > a[right])) {
          curr += (right - i - 1LL) * (left - l[left]) * a[left];
          left = l[left];
        } else {
          curr += (r[right] - right) * (i - 1LL - left) * a[right];
          right = r[right];
        }
      }
      cout << curr << ' ';
    }
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/