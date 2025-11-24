// Problem: CF 2021 C1 - Adjust The Presentation (Easy Version)
// https://codeforces.com/contest/2021/problem/C1

/* 
 * Problem: C1. Adjust The Presentation (Easy Version)
 * Algorithm: Simulation with position tracking
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(n) for arrays a, b, c
 *
 * We simulate the process of presenting slides and check whether each slide can be presented by the front member.
 * The key idea is to track positions of members in line and ensure that when a slide needs to be presented,
 * the required member is at the front of the line or has been moved there previously.
 * We maintain an array 'c' which marks if a position is occupied by a member who may have presented a slide.
 * If all positions needed are available, "YA" else "TIDAK".
 */
#include <iostream>
using namespace std;
#define endl '\n'
typedef long long ll;
int t, n, m, q, a[200005], b, c[200005];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  c[0] = 1; // Initialize first position as valid
  while (t--) {
    cin >> n >> m >> q;
    bool f = 1; // Flag to indicate if the presentation is good
    
    // Reset array a to store member positions in line
    for (int i = 1; i <= n; i++)
      cin >> b, a[b] = i, c[i] = 0; // Store position of each member and reset c[i]
    
    for (int j = 1; j <= m; j++) {
      cin >> b;
      // Mark the position where member 'b' was originally stood
      c[a[b]] = 1;
      
      // If the previous position is unmarked, it means that we didn't move member to front yet
      if (!c[a[b] - 1])
        f = 0;
    }
    
    if (f)
      cout << "YA\n";
    else
      cout << "TIDAK\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/