// Problem: CF 1890 D - Doremy's Connecting Plan
// https://codeforces.com/contest/1890/problem/D

/*
Algorithm/Technique: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(n) for prefix sum array

The problem asks whether we can connect all nodes in a graph by adding edges based on a specific condition.
We use a greedy strategy: always try to connect the current component to the node that gives the best chance of connectivity.
We maintain prefix sums to efficiently compute the total population of components.
The key observation is that we can always connect any node to node 1 if the sum of their populations meets the threshold.
We iterate from node 2 to n, and for each node, we check if we can connect it to node 1.
If yes, we update the population of node 1 to include all nodes up to the current one.
*/

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
template <class T> bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template <class T> bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pp;
#define int ll
#define lld long double
#define REP(x, y) for (int x = 0; x < y; ++x)
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define vt vector
#define f first
#define s second
#define pb push_back
#define PI atan(1) * 4
#define KickstarT(test_case) cout << "Case #" << test_case << ": "
#define endl '\n'
#define in(input) freopen(input, "r", stdin)
#define out(output) freopen(output, "w", stdout)
int d8[2][8] = {{-1, -1, 0, 1, 1, 1, 0, -1}, {0, 1, 1, 1, 0, -1, -1, -1}};
int d4[2][4] = {{-1, 0, 1, 0}, {0, 1, 0, -1}};
char dc[] = {'U', 'R', 'D', 'L'};
const int MD = 1e9 + 7;
void solve(int t_c) {
  int n, c;
  cin >> n >> c;
  vt<int> a(n + 1), p(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[i] = p[i - 1] + a[i];
  int f = 1;
  for (int i = 2; i <= n; i++) {
    if (a[1] + a[i] >= 1 * i * c) {
      a[1] = p[i];  // Update the population of node 1 to include all nodes up to i
      f = i;
    }
  }
  cout << (f == n ? "Yes" : "No") << endl;
}
#undef int
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  REP(i, t) { solve(i); }
  return 0;
}


// https://github.com/VaHiX/CodeForces/