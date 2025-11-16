// Problem: CF 1977 E - Tensor
// https://codeforces.com/contest/1977/problem/E

/*
 * Purpose: Solve an interactive problem involving coloring vertices of a directed graph
 *          under specific constraints. The graph satisfies a property that for any three vertices,
 *          at least one of them is reachable from another in a specific ordering.
 *          The task is to find a valid coloring (black/white) such that for any two vertices
 *          of the same color, one is reachable from the other.
 *
 * Algorithm:
 * - Use a greedy approach to assign colors based on reachability queries.
 * - Maintain tracking of the last two vertices that can reach the current vertex.
 * - Utilize a map 'col_must' to manage color assignments based on the logic.
 *
 * Time Complexity: O(n^2) in worst case due to queries, but bounded by 2*n queries as per problem constraints.
 * Space Complexity: O(n) for storing vertex colors and auxiliary variables.
 */

#include <stdint.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
const int64_t inf = 2e9;
const int64_t mod = 998244353;

void solve() {
  int64_t n;
  cin >> n;
  int64_t last1 = 1, last2 = -1, both = -1; // Track vertices for comparison logic
  vector<int> color(n); // Store color for each vertex (0 or 1)
  string answ; // Store response to queries
  int newCol = 2; // Counter for new color values
  map<int, int> col_must; // Map to translate our color indices to final 0/1 values
  col_must[0] = 0; // Base color mapping
  col_must[1] = 1;
  
  for (size_t i = 2; i <= n; i++) { // Iterate through vertices 2 to n
    if (both != -1) { // If we have a potential "both" vertex to check
      cout << "? " << both << ' ' << i << endl;
      cin >> answ;
      if (answ == "-1") {
        exit(0);
      }
      if (answ == "YES") {
        color[i - 1] = newCol; // Assign new color 
        both = i;
      } else {
        cout << "? " << last1 << ' ' << i << endl;
        cin >> answ;
        if (answ == "-1") {
          exit(0);
        }
        if (answ == "YES") {
          col_must[newCol] = 1; // Map new color to 1 (white)
          ++newCol;
          last2 = both;
          last1 = i;
          both = -1;
        } else {
          col_must[newCol] = 0; // Map new color to 0 (black)
          ++newCol;
          last1 = both;
          both = -1;
          color[i - 1] = 1; // Assign color 1 (black) to current vertex
          last2 = i;
        }
      }
      continue;
    }
    
    // Standard query of last1 to current vertex i
    cout << "? " << last1 << ' ' << i << endl;
    cin >> answ;
    if (answ == "-1") {
      exit(0);
    }
    if (answ == "YES" && last2 != -1) { // If last1 reaches i, and last2 is known
      cout << "? " << last2 << ' ' << i << endl;
      cin >> answ;
      if (answ == "-1") {
        exit(0);
      }
      if (answ == "YES") { // If both last1 and last2 can reach i
        both = i; // Mark i as potentially "both"
        color[i - 1] = newCol; // Assign a new color to i
      } else {
        last1 = i; // Update last1 as i cannot be reached from last2
        color[i - 1] = 0; // Color current vertex as black
      }
    } else if (answ == "YES") { // Only last1 can reach i
      last1 = i; // Update last1
      color[i - 1] = 0; // Color as black
    } else {
      last2 = i; // Update last2 as i is not reachable from last1
      color[i - 1] = 1; // Color as white
    }
  }
  
  // Output the final coloring
  cout << "! ";
  for (auto &&i : color) {
    cout << col_must[i] << ' '; 
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/