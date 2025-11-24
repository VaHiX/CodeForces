// Problem: CF 908 B - New Year and Buggy Bot
// https://codeforces.com/contest/908/problem/B

/*
 * Problem: B. New Year and Buggy Bot
 * 
 * Purpose: 
 *   Determine the number of valid digit-to-direction mappings that allow a robot 
 *   to reach the exit from the start position following the given instruction string.
 * 
 * Algorithm:
 *   - Try all permutations of the four directions (up, down, left, right) mapped to digits 0-3.
 *   - For each permutation, simulate the robot's path according to the instructions.
 *   - If the robot reaches the exit without crashing, increment the count.
 *   - A robot crashes if it goes out of bounds or hits an obstacle.
 * 
 * Time Complexity: O(4! * |s| * n * m) = O(24 * |s| * n * m)
 *   - 4! permutations of directions
 *   - For each permutation, simulate path of length |s|
 *   - Bounds checking and obstacle checking per move
 * 
 * Space Complexity: O(n * m + |s|) 
 *   - Store maze (n * m) and instruction string (|s|)
 * 
 * Techniques:
 *   - Permutation generation using next_permutation
 *   - Simulation of robot movement
 *   - Coordinate-based maze navigation
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 1010
#define inf 10000000
#define pp pair<int, int>
using namespace std;

int a[] = {0, 1, 2, 3}; // Direction indices: 0=up, 1=down, 2=left, 3=right
int n, m;
pp st, en; // Start and end positions
string s[55], t; // Maze grid and instruction string

int main() {
  int i, j, k;
  scanf("%d%d", &n, &m);
  for (i = 0; i < n; i++)
    cin >> s[i];
  cin >> t;
  
  // Find start and end positions
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (s[i][j] == 'S')
        st = {i, j};
      if (s[i][j] == 'E')
        en = {i, j};
    }
  }
  
  int cnt = 0; // Count of valid mappings
  int r, c; // Robot position coordinates
  j = 0;
  
  // Try all permutations of directions
  do {
    r = st.first, c = st.second; // Reset robot to start
    k = t.length(); // Length of instruction string
    j++;
    
    // Execute instructions for current mapping
    for (i = 0; i < k; i++) {
      // Map digit to direction and update position
      if (t[i] == a[0] + 48) // '0' maps to first direction
        r--;
      else if (t[i] == a[1] + 48) // '1' maps to second direction
        r++;
      else if (t[i] == a[2] + 48) // '2' maps to third direction
        c--;
      else // '3' maps to fourth direction
        c++;
      
      // Check for out-of-bounds
      if (r < 0 || r >= n || c < 0 || c >= m) {
        break;
      }
      
      // Check for obstacle
      if (s[r][c] == '#') {
        break;
      }
      
      // Check if reached exit
      if (s[r][c] == 'E') {
        cnt++; // Valid mapping found
        break;
      }
    }
  } while (next_permutation(a, a + 4)); // Generate next permutation of directions
  
  printf("%d", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/