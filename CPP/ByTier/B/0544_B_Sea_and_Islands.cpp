// Problem: CF 544 B - Sea and Islands
// https://codeforces.com/contest/544/problem/B

/*
 * Problem: B. Sea and Islands
 * 
 * Algorithm/Technique: Greedy approach to form exactly k islands on an n x n grid.
 * 
 * Approach:
 * - Fill the grid row by row, placing 'L' (land) cells in a pattern to create islands.
 * - For each row, place land cells at even indices (0, 2, 4, ...) alternating starting index.
 * - When k islands are formed, stop placing more and output the grid.
 * - If k exceeds the maximum possible number of islands (which is n * n / 2), output "NO".
 *
 * Time Complexity: O(n^2) - We traverse the grid at most once to fill it.
 * Space Complexity: O(n^2) - We store the n x n grid.
 */

#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 110
#define pp pair<int, int>
#define inf 10000000
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  cin >> n >> k;
  char **s = new char *[n];
  // Initialize the grid with all 'S' (sea)
  for (i = 0; i < n; i++) {
    s[i] = new char[n];
    for (j = 0; j < n; j++)
      s[i][j] = 'S';
  }
  m = 0;  // Starting column index for placing 'L' in each row
  int isle = 0;  // Count of current islands formed
  
  // Traverse the grid row by row to form islands
  for (i = 0; i < n; i++) {
    for (j = m; j < n; j += 2) {  // Place 'L' at even indices (0, 2, 4...)
      if (k == isle) {  // If we've formed all required islands
        cout << "YES\n";
        for (int x = 0; x < n; x++) {
          for (int y = 0; y < n; y++)
            cout << s[x][y];
          nl
        }
        return 0;
      }
      s[i][j] = 'L';  // Mark cell as land
      isle++;  // Increment island count
    }
    m = !m;  // Alternate starting column for next row (0 -> 1 or 1 -> 0)
  }
  
  // Check if we have exactly k islands after filling the grid
  if (k == isle) {
    cout << "YES\n";
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++)
        cout << s[x][y];
      nl
    }
    return 0;
  }
  
  // If we cannot form exactly k islands, output "NO"
  cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/