// Problem: CF 1677 C - Tokitsukaze and Two Colorful Tapes
// https://codeforces.com/contest/1677/problem/C

/*
 * Problem: Tokitsukaze and Two Colorful Tapes
 * Purpose: Find the maximum possible beauty of two colorful tapes by assigning distinct values to colors.
 * 
 * Algorithm:
 * 1. Process the two permutations to find cycles in the mapping of colors between the two tapes.
 * 2. For each cycle, we can assign values to minimize the sum of absolute differences.
 * 3. The maximum beauty is achieved by maximizing the contribution of each cycle:
 *    - For a cycle of length `cnt`, we can assign values such that they are as far apart as possible.
 *    - Assign the largest `cnt/2` values to one group of positions in the cycle,
 *      and the smallest `cnt/2` to the other.
 * 
 * Time Complexity: O(n) per test case due to processing each node only once.
 * Space Complexity: O(n) for storing the arrays and auxiliary data structures.
 */

#include <iostream>
#include <vector>

#define ll long long
#define N 200010
using namespace std;

vector<int> e[N]; // Not used in this code
int a[N], b[N], vis[N];

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, i, x, k = 0;
    ll ans = 0;
    cin >> n;
    
    // Read the first tape permutation
    for (i = 1; i <= n; i++)
      cin >> a[i];
    
    // Read the second tape permutation and store position of each color
    for (i = 1; i <= n; i++) {
      cin >> x;
      b[x] = i;  // b[color] = position in second tape
      vis[i] = 0;
    }
    
    // Find cycles in the mapping from first tape to second tape
    for (i = 1; i <= n; i++)
      if (!vis[i]) {
        vis[i] = 1;
        int nw = i, cnt = 1;
        // Traverse the cycle until we return to start
        while (!vis[b[a[nw]]])
          nw = b[a[nw]], cnt++, vis[nw] = 1;
        k += cnt / 2;  // Add half the size of the cycle to k
      }
    
    // Compute maximum beauty using the formula
    for (i = 1; i <= k; i++)
      ans += (n - i + 1 - i) * 2;
    
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/