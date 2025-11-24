// Problem: CF 1738 F - Connectivity Addicts
// https://codeforces.com/contest/1738/problem/F

/*
Algorithm: Greedy coloring with connectivity maintenance
Approach:
1. Sort vertices by degree in ascending order
2. Process vertices from highest degree to lowest
3. For each uncolored vertex, perform BFS/DFS to find connected component
4. Assign color to all vertices in the connected component
5. Use queries to discover neighbors and maintain connectivity

Time Complexity: O(n^2) in worst case due to nested loops and sorting
Space Complexity: O(n) for storing vertex information, colors, and stack
*/
#include <algorithm>
#include <iostream>

using namespace std;
const int o = 1010;
int T, n, d[o], p[o], col[o], st[o], tp;
inline bool cmp(int A, int B) { return d[A] < d[B]; }
int main() {
  for (cin >> T; T--; cout << endl) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> d[i], p[i] = i, col[i] = 0;
    sort(p + 1, p + n + 1, cmp);
    for (int i = n, asd = 0; i; --i)
      if (!col[p[i]]) {
        st[tp = 1] = p[i]; // Start BFS/DFS with current vertex
        for (int x, D = d[p[i]]; D--;) {
          cout << "? " << p[i] << endl;
          cin >> x;
          if (col[x]) {
            // If neighbor is already colored, merge components
            for (; tp; col[st[tp--]] = col[x])
              ;
            break;
          } else
            st[++tp] = x; // Add neighbor to stack for exploration
        }
        if (tp)
          for (++asd; tp; col[st[tp--]] = asd)
            ; // Assign new color to all vertices in component
      }
    cout << "!";
    for (int i = 1; i <= n; ++i)
      cout << " " << col[i];
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/