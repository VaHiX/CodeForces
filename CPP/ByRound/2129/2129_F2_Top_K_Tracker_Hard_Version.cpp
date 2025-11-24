// Problem: CF 2129 F2 - Top-K Tracker (Hard Version)
// https://codeforces.com/contest/2129/problem/F2

/*
 * F2. Top-K Tracker (Hard Version)
 * 
 * Purpose: This code attempts to reconstruct a hidden permutation p of {1, 2, ..., n} 
 *          using up to 30 queries of four types (1, 2, 3, 4), each returning top-k
 *          values according to specified criteria.
 *          
 * Algorithm/Techniques:
 *   - Uses precomputed subsets of integers from 1 to 29 for query construction.
 *   - Employs strategies based on position and value tracking via queries.
 *   - Uses randomization in type selection to shuffle and reconstruct permutation.
 *   
 * Time Complexity: O(n^2) - mainly due to nested loops for constructing and processing
 *                    queries; the main logic is bounded by number of queries and fixed
 *                    precomputed data of size ~450.
 * Space Complexity: O(n^2) - since we store various structures such as vectors, maps,
 *                    and arrays up to size n * 29 for storing queries and their mappings.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;
int t, n, a[895], pos[895];
bool type[450];
vector<vector<int>> p; // Precomputed query patterns
map<vector<int>, int> id; // Mapping from pattern to ID for efficient lookup
int main() {
  srand(time(0)), p.push_back(vector<int>()); // Initialize with empty vector
  for (int i = 1; i <= 29; i++)               // Single elements from 1 to 29
    p.push_back(vector<int>(1, i));
  p.push_back(vector<int>()); // Add one more empty vector for consistency
  for (int i = 1; i <= 29; i++)
    for (int j = i + 1; j <= 29; j++)              // Pairs from 1 to 29
      p.push_back((vector<int>){i, j});
  for (int k = 0; k < 9; k++)                      // Groups of three elements with interval 9
    p.push_back((vector<int>){k + 1, k + 10, k + 19});
  for (int i = 1; i <= 445; i++)                   // Map patterns to index
    id[p[i]] = i;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> q[35], e[895]; // q stores query results per element; e stores inverse mapping from positions
    for (int i = 1; i <= n / 2; i++)
      for (int j = 0; j < p[i].size(); j++)
        q[p[i][j]].push_back(i), q[p[i][j]].push_back(n - i + 1); // Build query pattern queries
    if (n & 1)
      for (int j = 0; j < p[n / 2 + 1].size(); j++)
        q[p[n / 2 + 1][j]].push_back(n / 2 + 1);  // Handle odd case center element

    for (int i = 1; i < 30; i++) {
      if (q[i].empty()) continue; // Skip if no query data
      cout << 2 << ' ' << q[i].size() << ' ';      // Type 2 query with size of q[i]
      for (int j = 0; j < q[i].size(); j++)
        cout << q[i][j] << (j == q[i].size() - 1 ? '\n' : ' '); // Output the indexes being queried
      fflush(stdout);
      for (int j = 0, t; j < q[i].size(); j++)
        cin >> t, e[t].push_back(i);   // Read back result indices
    }

    for (int i = 1; i <= n; i++) {
      if (pos[id[e[i]]])             // If already filled
        pos[n - id[e[i]] + 1] = i;   // Mirror fill
      else
        pos[id[e[i]]] = i;           // Otherwise direct assign to position
    }

    cout << 3 << ' ' << n / 2 << ' '; // Output type 3 query with n/2 elements
    for (int i = 1; i <= n / 2; i++)
      type[i] = rand() & 1,          // Randomly decide whether to use symmetric index or not
      cout << pos[type[i] ? n - i + 1 : i] << (i == n / 2 ? '\n' : ' '); // Print positions accordingly
    fflush(stdout);
    set<int> temp;
    for (int i = 1, t; i <= min(n / 2, 300); i++)
      cin >> t, temp.insert(t);   // Read top K values and insert

    for (int i = 1; i <= n / 2; i++)
      if ((temp.find(n - i + 1) != temp.end()) ^ type[i]) // XOR condition to adjust symmetry
        swap(pos[i], pos[n - i + 1]); // Swap positions if needed

    for (int i = 1; i <= n; i++)
      a[pos[i]] = i, pos[i] = 0; // Finalize mapping from position to value

    cout << "! ";
    for (int i = 1; i <= n; i++)
      cout << a[i] << (i == n ? '\n' : ' '); // Output the final permutation
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/