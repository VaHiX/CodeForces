// Problem: CF 1774 B - Coloring
// https://codeforces.com/contest/1774/problem/B

/*
Purpose: To determine if it's possible to color a paper tape of n cells with m colors such that:
         - Each color i is used exactly a[i] times.
         - Every k consecutive cells have distinct colors.
         
Algorithms/Techniques: 
    Greedy approach based on distribution of color counts.
    - We divide n cells into groups of k consecutive cells (with possible remainder).
    - For each group, we can place at most k distinct colors.
    - We ensure no color count exceeds the maximum allowed per group (vl + 1), or else it's impossible.
    - We also check how many colors exceed (vl + 1) and compare with the number of "extra" positions (x).

Time Complexity: O(m) per test case, since we iterate through the array of size m once.
Space Complexity: O(1) as we only use a fixed-size array of size m and a few variables.
*/

#include <stddef.h>
#include <iostream>

using namespace std;
#define int long long
#define pb push_back
#define pob pop_back
#define endl "\n"
#define vi vector<int>
#define pii pair<int, int>
#define MOD 1000000007
#define inf 1e18
#define ff first
#define ss second
#define fo(i, a, b) for (int i = a; i < b; i++)
#define rfo(i, a, b) for (int i = a; i >= b; i--)
#define test int t
#define fast                                                                   \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  int a[m]; // Array to store the count of each color
  fo(i, 0, m) cin >> a[i];
  
  int vl = n / k; // Base number of times each color can be used (in groups of k)
  int x = n % k;  // Remaining cells after grouping into k-sized chunks
  
  int cnt = 0; // Count of colors that require more than (vl + 1) uses
  
  fo(i, 0, m) {
    if (a[i] > vl) {
      if (a[i] > (vl + 1)) {
        cout << "NO" << endl;
        return;
      } else
        cnt++; // Color can fit in one extra slot at most
    }
  }
  
  // If more colors need to exceed vl+1 than available extra positions, it's impossible
  if (cnt > x)
    cout << "NO" << endl;
  else
    cout << "YES" << endl;
}
signed main() {
  fast int t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/