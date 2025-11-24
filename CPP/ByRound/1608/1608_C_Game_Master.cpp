// Problem: CF 1608 C - Game Master
// https://codeforces.com/contest/1608/problem/C

/*
Algorithm: 
The solution determines which players can potentially win a tournament by simulating
a process where players are eliminated based on their strengths on two maps.
It uses a greedy strategy to identify winners by considering the rankings of players
on both maps and eliminating those who are dominated in any ranking.

Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing player data and auxiliary arrays

Techniques:
- Sorting players based on strength values on both maps
- Greedy approach to determine potential winners
- Tracking of elimination status using a boolean array
*/

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
const int N = 1e6;
int t, n, A[N], v[N], c, x, y;
pair<int, int> a[N], b[N];
int main() {
  cin >> t;
  while (t-- && cin >> n) {
    // Initialize player data for both maps
    for (int i = 1; i <= n; i++)
      cin >> a[i].first, a[i].second = i, A[i] = v[i] = 0;
    for (int i = 1; i <= n; i++)
      cin >> b[i].first, b[i].second = i;
    
    // Sort players by strength on each map
    sort(a + 1, a + n + 1), sort(b + 1, b + n + 1), c = 0;
    
    // Process players in descending order of strength on both maps
    for (int i = n; i; i--) {
      x = a[i].second, y = b[i].second, c += !v[x], v[x] = 1, c += !v[y],
      v[y] = A[x] = 1;
      if (c == n - i + 1)
        break;
    }
    
    // Output result for each player
    for (int i = 1; i <= n; i++)
      cout << A[i];
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/