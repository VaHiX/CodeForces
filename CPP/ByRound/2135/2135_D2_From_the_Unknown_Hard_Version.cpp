// Problem: CF 2135 D2 - From the Unknown (Hard Version)
// https://codeforces.com/contest/2135/problem/D2

/*
 * Problem: D2. From the Unknown (Hard Version)
 * Purpose: Determine the width parameter W of the RiOI Editor through at most 2 interactive queries.
 * Algorithm: Binary search with carefully crafted queries to narrow down the value of W.
 * Time Complexity: O(log N), where N is up to 1e5. Each query involves processing a limited number of elements.
 * Space Complexity: O(1), only using fixed-size variables and no additional data structures grow with input.
 *
 * Techniques:
 * - Interactive Binary Search
 * - Adaptive querying strategy based on results
 * - Efficient use of constraints (sum of lengths <= 2.5e4)
 */

#include <iostream>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second
#define sep ' '
#define SZ(x) ll(x.size())
const ll M = 15400;
const ll N = 1e5;
const ll K = 125;
const ll T = 12;
const ll LOG = 22;
const ll INF = 8e18;
const ll MOD = 1e9 + 7;
int q;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> q;
  while (q--) {
    ll sz = N / K * T;  // Compute initial size of first query
    cout << "? " << sz << " ";  // Start the first query
    for (int i = 0; i < T * N / K; i++) {  // Add K repeated values to form a long line
      cout << K << sep;
    }
    cout << endl;
    int x;
    cin >> x;  // Read result of first query
    if (x == 0) {
      // Case: Editor cannot display the query article, meaning W < sum of lengths.
      cout << "? " << M << " ";  // Try another specific query pattern
      for (int i = 1; i <= M; i++) {
        cout << 1 << sep;
      }
      cout << endl;
      cin >> x;  // Read result from second query
      // Final calculation: Estimate W as (M + x - 1) / x, which gives a lower bound
      cout << "! " << (M + x - 1) / x << endl;
      continue;
    }
    if (x == T) {
      // Case: Editor displays the query article in exactly T lines — means W >= the sum of lengths
      cout << "! " << N << endl;
      continue;
    }
    // General case:
    // Use binary search bounds derived from first two queries
    int L = (sz + x - 1) / x * K, R = (sz - 1) / (x - 1) * K + K - 1;
    if (L == R) {
      // Narrowed down to single value
      cout << "! " << L << endl;
      continue;
    }
    // Final query: ask about elements between L and R with specific pattern
    cout << "? " << 2 * (R - L) << " ";
    for (int i = L + 1; i <= R; i++) {
      cout << L << sep << i - L << sep;  // Special pairing for binary search refinement
    }
    cout << endl;
    cin >> x;  // Read result of final query
    // Final result based on computed offset
    cout << "! " << R - x + (R - L) << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/