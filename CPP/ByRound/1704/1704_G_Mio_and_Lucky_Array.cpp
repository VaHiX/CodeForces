// Problem: CF 1704 G - Mio and Lucky Array
// https://codeforces.com/contest/1704/problem/G

/*
Algorithm: 
The problem requires transforming array 'a' into an array that contains 'b' as a subarray using specific operations.
The key insight is that each operation on index i modifies elements a[i], a[i+1], a[i+2], ... according to a specific pattern.
The approach is to:
1. Precompute a 'difference' array to represent the expected changes needed to match 'b'
2. Check each possible starting position in 'a' where 'b' could be a subarray
3. Verify if the constraints can be satisfied with the given operations
4. For valid positions, determine the precise operations needed

Time Complexity: O(n^2) in worst case due to checking all possible positions and operations
Space Complexity: O(n) for storing arrays and auxiliary data structures

This solution uses mathematical analysis to determine if a valid sequence of operations exists and computes them.
*/

#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;
#define N 200010
#define LL long long
int T, n, m, a[N];
LL b[N], f[N];
pair<LL, int> g[N];
bitset<N> ok, t;
map<LL, vector<int>> mp;

// Helper function for quadratic evaluation
LL F(LL A, LL B, LL C, LL x) { return A * x * x + B * x + C; }

// Check if a subarray starting at position 'st' can match 'b'
bool check(int st) {
  LL d0 = b[0] - a[st], d1 = b[1] - a[st + 1]; // Calculate differences
  LL k = d0 + d1, M = st & 1 ? st : (st + 1), M_ = st & 1 ? (st + 1) : st; // Determine shift values
  LL nx = st / 2 + 1, ny = (st + 3) / 2; // Determine bounds
  LL l = max(0ll, -k), r = min(nx, ny - k); // Compute valid range
  LL o = d0 & 1; // Parity check
  if (l % 2 != o)
    l++;
  if (r % 2 != o)
    r--;
  if (l > r)
    return false; // No valid operations in range
  
  // Evaluate minimum and maximum values of the quadratic function
  LL A = -2, B = M - 2ll * k + 2, C = k - k * k;
  LL x0 = -B / (2ll * A);
  LL mn = 1e18, mx = -mn;
  for (LL i = x0 - 5; i <= x0 + 5; i++)
    if (i % 2 == o && l <= i && i <= r)
      mx = max(mx, F(A, B, C, i));
  mx = max(mx, F(A, B, C, l));
  mx = max(mx, F(A, B, C, r));
  
  A = 2, B = 2ll * k - M_ - 1, C = k * k - (M_ + 1) * k;
  x0 = -B / (2ll * A);
  for (LL i = x0 - 5; i <= x0 + 5; i++)
    if (i % 2 == o && l <= i && i <= r)
      mn = min(mn, F(A, B, C, i));
  mn = min(mn, F(A, B, C, l));
  mn = min(mn, F(A, B, C, r));
  
  // Check if the required value d0 falls within the valid range
  if (d0 > mx || d0 < mn)
    return false;
    
  LL x = -1;
  // Find the optimal operation position
  for (LL i = l; i <= r; i++)
    if (i % 2 == o) {
      mn = F(A, B, C, i);
      mx = F(-2, M - 2ll * k + 2, k - k * k, i);
      if (mn <= d0 && d0 <= mx) {
        x = i;
        break;
      }
    }
  set<int> ans;
  LL s = 0, y = x + k;
  // Add operations to make necessary changes
  for (LL i = 0; i < x; i++)
    s += 2ll * i + 1, ans.insert(st - 2ll * i);
  for (LL i = 0; i < y; i++)
    s -= 2ll * i, ans.insert(st - 2ll * i + 1);
    
  // Adjust the solution using the remaining differences
  for (LL i = x - 1; i >= 0 && s < d0; i--) {
    s -= 2ll * i + 1;
    ans.erase(st - 2ll * i);
    while (s + M > d0)
      M -= 2;
    s += M;
    ans.insert(st - M + 1);
    M -= 2;
  }
  for (LL i = y - 1; i >= 0 && s > d0; i--) {
    s += 2ll * i;
    ans.erase(st - 2ll * i + 1);
    while (s - M_ < d0)
      M_ -= 2;
    s -= M_;
    ans.insert(st - M_ + 1);
    M_ -= 2;
  }
  
  // Add fixed points from the pattern matching
  for (LL i = 2; i < m; i++)
    if (f[st + i] == g[i].first - 1)
      ans.insert(st + i);
      
  printf("%d\n", (int)ans.size());
  for (auto i : ans)
    printf("%d ", i + 1);
  printf("\n");
  return true;
}

// Initialize data structures and check all possible positions
void init() {
  mp.clear();
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]), ok[i] = 1;
  scanf("%d", &m);
  for (int i = 0; i < m; i++)
    scanf("%lld", &b[i]);
    
  // Compute differences for pattern matching
  for (int i = 2; i < n; i++)
    mp[f[i] = a[i] + 2 * a[i - 1] + a[i - 2]].push_back(i);
  for (int i = 2; i < m; i++)
    g[i] = make_pair(b[i] + 2ll * b[i - 1] + b[i - 2], i);
    
  sort(g + 2, g + m);
  for (int i = 2; i < m;) {
    t.reset(); 
    for (auto j : mp[g[i].first])
      t[j] = 1;
    for (auto j : mp[g[i].first - 1])
      t[j] = 1;
    int j = i;
    while (j < m && g[j].first == g[i].first)
      ok &= t >> g[j].second, j++;
    i = j;
  }
  
  // Reinitialize pattern matching
  for (int i = 2; i < m; i++)
    g[i] = make_pair(b[i] + 2ll * b[i - 1] + b[i - 2], i);
    
  // Check each possible starting position
  for (int i = 0; i <= n - m; i++)
    if (ok[i])
      if (check(i))
        return;
  printf("-1\n");
}

// Main function that iterates over test cases
int main() {
  scanf("%d", &T);
  while (T--)
    init();
}


// https://github.com/VaHiX/CodeForces/