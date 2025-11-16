// Problem: CF 1896 C - Matching Arrays
// https://codeforces.com/contest/1896/problem/C

/*
Algorithm/Technique: Greedy + Sorting
Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing arrays and temporary data

This problem involves determining if we can rearrange array b such that 
exactly x positions satisfy a[i] > b[i]. The approach is to sort both arrays 
and then greedily assign elements from b to positions in a to achieve exactly x 
such pairs. It uses a two-pointer like strategy:
- First, assign smallest elements of b to positions where a[i] > b[i] is required (x times)
- Then, assign remaining elements to positions where a[i] <= b[i] must hold
*/

#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
#define fi first
#define se second
#define arr(a, n) (a) + 1, (a) + n + 1
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
#define MASK(i) (1LL << (i))
#define TimeComplexity()                                                       \
  cerr << "\nTime Elapse: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n"
const int N = 2e5 + 5;
int n, x, res[N];
ii a[N], b[N];

void Process() {
  cin >> n >> x;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i].fi;
    a[i].se = i;  // Store original index
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i].fi;
    b[i].se = i;  // Store original index
  }
  
  sort(arr(a, n));  // Sort array a by value
  sort(arr(b, n));  // Sort array b by value
  
  int j = n - x + 1;  // Index in b to start assigning for a[i] > b[i]
  // Assign first x elements of b to positions where a[i] > b[i] must hold
  for (int i = 1; i <= x; ++i) {
    res[a[j].se] = b[i].fi;
    if (a[j].fi <= b[i].fi) {  // Check if condition a[i] > b[i] would be violated
      cout << "NO\n";
      return;
    }
    ++j;
  }
  
  j = 1;  // Reset index to start assigning remaining elements
  // Assign rest of elements to positions where a[i] <= b[i] must hold
  for (int i = x + 1; i <= n; ++i) {
    res[a[j].se] = b[i].fi;
    if (a[j].fi > b[i].fi) {  // Check if condition a[i] <= b[i] would be violated
      cout << "NO\n";
      return;
    }
    ++j;
  }
  
  cout << "YES\n";
  for (int i = 1; i <= n; ++i)
    cout << res[i] << " ";
  cout << "\n";
}

int main() {
#define file "INP"
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  if (fopen(file ".INP", "r")) {
    freopen(file ".INP", "r", stdin);
    freopen(file ".OUT", "w", stdout);
  }
  int t;
  cin >> t;
  while (t--) {
    Process();
  }
  TimeComplexity();
  return 0;
}


// https://github.com/VaHiX/CodeForces/