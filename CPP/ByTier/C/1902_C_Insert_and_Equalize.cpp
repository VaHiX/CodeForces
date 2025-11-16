// Problem: CF 1902 C - Insert and Equalize
// https://codeforces.com/contest/1902/problem/C

/*
Algorithm:
- The problem asks to insert one element and then make all elements equal using
operations of adding a fixed value x.
- The key insight is to find the optimal x (which will be the GCD of differences
between adjacent elements in sorted array) and choose an optimal insertion
point.
- After sorting the array, compute GCD of all differences between consecutive
elements.
- Then calculate the total operations needed considering the optimal insertion
point.
- Time Complexity: O(n log n) due to sorting and GCD computation.
- Space Complexity: O(n) for storing the array and prefix differences.

Approach:
1. Sort the array.
2. Calculate differences between consecutive elements.
3. Compute GCD of all differences.
4. Compute total operations needed.
5. Consider different insertion points and adjust accordingly.
*/
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <ctype.h>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <stdio.h>
#include <string.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define pll pair<long long, long long>
#define vll vector<long long>
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sz(x) (long long)(x).size()
#define endl "\n"

long long gcd(long long a, long long b) {
  if (b > a) {
    return gcd(b, a);
  }
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

void solve() {
  int n;
  cin >> n;
  vector<long long> v(n);
  long long result = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  if (n == 1) {
    cout << "1\n";
  } else {
    sort(v.begin(), v.end());
    // Compute differences between adjacent elements
    vector<long long> ps(n - 1);
    for (int i = 0; i < n - 1; ++i) {
      ps[i] = v[i + 1] - v[i];
    }
    // Find GCD of all differences
    long long gd = ps[0];
    for (int i = 1; i < n - 1; ++i) {
      gd = gcd(gd, ps[i]);
    }
    // Calculate base operations needed
    for (int i = 0; i < n; ++i) {
      result += (v[n - 1] - v[i]) / gd;
    }
    // Check if we need alternative insertion
    bool flag = false;
    int an1 = 0;
    for (int i = n - 2; i >= 0; --i) {
      if (gd < ps[i]) {
        flag = true;
        an1 = v[i + 1] - gd;
        break;
      }
    }
    if (flag) {
      // If alternate insertion is better
      result += (v[n - 1] - an1) / gd;
    } else {
      // If original insertion is best, add n operations (insert at beginning or
      // end)
      result += n;
    }
    cout << result << endl;
  }
}

int main() {
  int tt;
  cin >> tt;
  while (tt--)
    solve();
}

// https://github.com/VaHiX/CodeForces/