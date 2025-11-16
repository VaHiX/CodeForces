// Problem: CF 2057 G - Secret Message
// https://codeforces.com/contest/2057/problem/G

/*
 * Problem: G. Secret Message
 *
 * Purpose: Given a grid where '#' represents free cells and '.' represents blocked cells,
 *          find a minimal set S of free cells such that every free cell is either in S
 *          or adjacent to a cell in S. The size of S must be at most 1/5 * (s + p),
 *          where s is the number of free cells and p is the perimeter of the figure formed
 *          by the union of free cells.
 *
 * Approach:
 * - For each free cell '#', we associate it with a bucket based on (i + 2*j) % 5.
 * - For each free cell '#', we also consider its adjacent cells that are either out of bounds
 *   or blocked ('.') and assign these to buckets based on (x + 2*y + 20) % 5.
 * - The idea is to use a greedy approach by selecting the smallest bucket as the set S.
 *
 * Time Complexity: O(n * m) per test case, as each cell is processed a constant number of times.
 * Space Complexity: O(n * m) for storing the grid and buckets.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define endl '\n'
#define pb push_back
#define F first
#define S second
#define mk make_pair
typedef long long ll;
const int N = 2e6 + 7;
int n, m;
char a[N];  // Stores the grid
vector<int> vec[5];  // Buckets for grouping cells
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};  // Directions for adjacent cells
int f(int i, int j) { return i * m + j; }  // Converts 2D coordinates to 1D index

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int q;
  cin >> q;
  while (q--) {
    cin >> n >> m;
    // Read input grid
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> a[f(i, j)];
      }
    }
    
    // Process each free cell and assign to buckets
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int k = f(i, j);
        if (a[k] != '#')  // Only process free cells
          continue;
        vec[(i + 2 * j) % 5].pb(k);  // Assign cell to bucket based on (i + 2*j) % 5
        
        // Check adjacent cells for boundary conditions
        for (int h = 0; h < 4; h++) {
          int x = i + dx[h], y = j + dy[h];
          if ((x < 0 || x >= n || y < 0 || y >= m) || a[f(x, y)] == '.') {
            // If adjacent cell is out of bounds or blocked, add to bucket
            vec[(x + 2 * y + 20) % 5].pb(k);
          }
        }
      }
    }
    
    int sum = 0;
    for (int i = 0; i < 5; i++)
      sum += vec[i].size();
    
    // Select the smallest bucket to form set S
    for (int i = 0; i < 5; i++) {
      if (vec[i].size() <= sum / 5) {
        for (auto k : vec[i])
          a[k] = 'S';  // Mark cells in S
        break;
      }
    }
    
    // Clear buckets for next iteration
    for (int i = 0; i < 5; i++)
      vec[i].clear();
    
    // Output the result grid
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << a[f(i, j)];
      }
      cout << endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/