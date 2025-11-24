// Problem: CF 1982 C - Boring Day
// https://codeforces.com/contest/1982/problem/C

/*
Algorithm: Two Pointers (Sliding Window)
Purpose: To find the maximum number of rounds Egor can win by taking cards from the top of the deck such that the sum of each round is between l and r (inclusive).
Time Complexity: O(n) where n is the number of cards, since each element is visited at most twice (once by r pointer, once by l pointer).
Space Complexity: O(1) as we use only a constant amount of extra space.
*/
#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;
#define printArr(arr)                                                          \
  for (auto x : arr)                                                           \
    cout << x << " ";                                                          \
  cout << '\n'
#define print2DArr(arr)                                                        \
  for (auto &x : arr) {                                                        \
    printArr(x);                                                               \
  }
#define forn(i, n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define pb(x) push_back(x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define tests                                                                  \
  int tt;                                                                      \
  cin >> tt;                                                                   \
  while (tt--)
#define f first
#define s second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vpi = vector<pii>;
using vpl = vector<pll>;
using iii = tuple<int, int, int>;
const ll inf = 1e18;
const int MOD = 1e9 + 7;
const long double EPS = 1e-9;
int main() {
  cin.tie(0)->sync_with_stdio(0);
  tests {
    int n, left, right;
    cin >> n >> left >> right;
    vi nums(n);
    forn(i, n) cin >> nums[i];
    int l = 0, r = 0;
    int sum = 0;
    int res = 0;
    int ind = 0;
    while (l < n) {
      // Expand window to the right until sum is at least 'left'
      while (r < n && sum < left)
        sum += nums[r++];
      // If current sum is within [left, right], we can win this round
      if (left <= sum && sum <= right) {
        res++;
        l = r;  // Move left pointer to right
        sum = 0; // Reset sum
      } else
        sum -= nums[l++]; // Shrink window from left
    }
    cout << res << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/