// Problem: CF 1875 D - Jellyfish and Mex
// https://codeforces.com/contest/1875/problem/D

/*
 * Problem: Jellyfish and Mex
 * 
 * Purpose: Compute the minimum possible final value of m after performing n operations,
 *          where each operation selects an element from the array, removes it,
 *          and adds the MEX of the remaining array to m.
 * 
 * Approach:
 * - Use dynamic programming to determine the optimal way to remove elements,
 *   minimizing the total contribution to m.
 * - The key insight is to bound each element to n (since MEX cannot exceed n),
 *   because MEX of an array with size n can only be in [0, n].
 * - Build a frequency count of elements in [0, n]
 * - Compute MEX of initial array and use it as a key in DP
 * - Use DP: f[i] represents minimum cost to make MEX at least i
 * 
 * Time Complexity: O(n^2) per test case
 * Space Complexity: O(n) per test case
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf = 1e9;
const ll llnf = 4e18;

template <class Tp> void chkmax(Tp &x, Tp y) { x = max(x, y); }
template <class Tp> void chkmin(Tp &x, Tp y) { x = min(x, y); }

void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  // Clamp each value to at most n to avoid unnecessary large MEXs
  for (int i = 1; i <= n; i++)
    cin >> a[i], a[i] = min(a[i], n);
  
  // Count frequency of values in range [0, n]
  vector<int> c(n + 1);
  for (int i = 1; i <= n; i++)
    c[a[i]]++;
  
  // Find initial MEX of the array
  int mex = 0;
  while (c[mex])
    mex++;
  
  // DP: f[i] = minimum cost to have MEX >= i
  vector<int> f(n + 1, inf);
  f[mex] = 0;  // Base case: if current MEX is already mex, cost is 0

  // Fill DP from larger indices to smaller ones
  for (int i = mex - 1; i >= 0; i--)
    for (int j = i + 1; j <= mex; j++)
      // For each possible next state, update the minimum cost
      chkmin(f[i], f[j] + c[i] * j);
  
  // Output final result: f[0] minus the final MEX (which is added from last operation)
  cout << f[0] - mex << "\n";
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/