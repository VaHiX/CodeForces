// Problem: CF 1973 E - Cat, Fox and Swaps 
// https://codeforces.com/contest/1973/problem/E

/*
 * Problem: E. Cat, Fox and Swaps
 * 
 * Algorithm:
 *   - The key idea is to understand when we can sort the array using allowed swaps.
 *   - A swap is allowed between elements x and y if l <= x + y <= r.
 *   - If the array is already sorted, then all intervals [l,r] where 1 <= l <= r <= 2*n are valid.
 *     There are (2*n)*(2*n+1)/2 such pairs.
 *   - Otherwise, we must identify a specific "conflict" value (the sum of misplaced element positions).
 *     If multiple elements are not in their correct positions, and they don't all sum to the same value,
 *     it's impossible to sort with any range.
 *     Otherwise, we compute the minimal valid range needed to fix all misplaced elements.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for input storage
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5, mod = 998244353;

void solve() {
  int n;
  cin >> n;
  vector<int> p(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> p[i];
  
  // Check if array is already sorted
  int ok = 0;
  for (int i = 1; i <= n; i++) {
    if (p[i] != i) {
      if (ok == -1)
        break;
      if (ok == 0)
        ok = i + p[i];  // store sum of first misplaced pair
      else if (ok != i + p[i])
        ok = -1;        // inconsistency - not possible to sort
    }
  }
  
  // If array is sorted, count all valid (l,r) pairs
  if (ok == 0) {
    cout << 1ll * n * 2 * (2 * n - 1) / 2 + 2 * n << endl;
    return;
  } else {
    // Determine range of misplaced elements
    int l = n + 1, r = 0;
    for (int i = 1; i <= n; i++)
      if (p[i] != i)
        r = i;  // rightmost misplaced index
    
    for (int i = n; i; i--)
      if (p[i] != i)
        l = i;  // leftmost misplaced index
    
    ll ans = 0;
    l += n;  // adjust to correct value for sum calculation
    r++;     // adjust to correct bound
    
    // For each valid r, add number of valid l values
    for (int i = r; i <= 2 * n; i++) {
      ans += min(l, i - 1);
    }
    
    if (ok > 0)
      ans++;  // add 1 for case where l <= ok <= r
    
    cout << ans << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/