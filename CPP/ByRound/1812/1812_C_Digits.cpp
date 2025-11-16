// Problem: CF 1812 C - Digits
// https://codeforces.com/contest/1812/problem/C

/*
Purpose: This code solves a problem where for each test case, we read a number 'k' and then 'k' integers.
         We compute the product of these 'k' integers and output the result.

Algorithms/Techniques: 
- Iteration through input data
- Simple arithmetic product calculation
- Use of precomputed string for digit mapping

Time Complexity: O(sum of all n across test cases), where n is the number of integers per test case.
Space Complexity: O(1), since we only use a fixed amount of extra space (not counting input storage).

*/

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define task ""
#define speed()                                                                \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0)
#define endl '\n'
#define mems(a, v) memset(a, v, sizeof(a))
#define all(v) v.begin(), v.end()
#define rev(v) reverse(all(v))
#define sz(v) v.size()
#define dbg(x) cout << (#x) << " = " << x << endl
#define dbg2(x, y)                                                             \
  cout << (#x) << " = " << x << ", " << #y << " = " << y << endl
#define f first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back
#define gcd __gcd
#define pi 3.1415926535897932384626
#define BFS_BLACK 1
#define BFS_WHITE -1
#define BFS_GREY 2
#define DFS_BLACK 1
#define DFS_WHITE -1
#define DFS_GREY 2
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll, ll>> vii;
typedef vector<vi> vvi;
const ll maxn = 1e5 + 7;
const ll mod = 1e9 + 7;
const ll inf = 1e18;
const ll da[] = {-1, 0, 1, 0};
const ll db[] = {0, 1, 0, -1};
const ll dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const ll dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
string pi1 = "31415926535897932384626433832795028841971693993751058209749445923"
             "07816406286208998628034825342";
ll ti;
void solve() {
  ll ans = 1; // Initialize the product to 1
  ll k = pi1[ti - 1] - '0'; // Get the digit from precomputed string based on test case index
  for (ll j = 1; j <= k; ++j) {
    ll x;
    cin >> x; // Read the next integer
    ans = ans * x; // Multiply it to the running product
  }
  cout << ans << endl; // Output the result
}
signed main() {
  speed();
  ll t = 1;
  cin >> t;
  for (ll _ = 1; _ <= t; _++) {
    ti = _; // Set current test case index
    solve(); // Solve for this test case
  }
}


// https://github.com/VaHiX/CodeForces/