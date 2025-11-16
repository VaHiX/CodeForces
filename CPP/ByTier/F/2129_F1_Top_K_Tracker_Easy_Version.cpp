// Problem: CF 2129 F1 - Top-K Tracker (Easy Version)
// https://codeforces.com/contest/2129/problem/F1

// Flowerbox:
// Problem: Top-K Tracker (Easy Version)
// Purpose: Recover a hidden permutation p of {1,2,...,n} using four types of queries.
// Algorithms/Techniques:
//   - Interactive problem solving using 4 query types to gather information about positions and values in the permutation.
//   - Uses pre-defined patterns in vectors p[] to efficiently guess structure and relationships.
//   - Applies sorting and map lookups for mapping vector patterns back to indices.
// Time Complexity: O(n * log(n)) due to sorting and map operations, bounded by n≤845.
// Space Complexity: O(n^2) for storing query results and vectors, but effectively much smaller due to pre-defined p pattern construction.

#include <algorithm>
#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>
using namespace std;

int t, n, a[850];
vector<vector<int>> p; // Predefined vector patterns for querying
map<vector<int>, int> id; // Map to store index of each pattern in p for quick lookup

int main() {
  // Initialize p with predefined patterns to help deduce the permutation
  p.push_back(vector<int>());
  for (int i = 1; i <= 30; i++)
    p.push_back(vector<int>(1, i)); // Single element vectors [1], [2], ..., [30]
  
  p.push_back(vector<int>()); // Dummy empty vector
  for (int i = 1; i <= 30; i++)
    for (int j = i + 1; j <= 30; j++)
      p.push_back((vector<int>){i, j}); // Two-element vectors [i,j] for all pairs where i < j
  
  // Add sequences of three elements using modular arithmetic
  for (int i = 1; i <= 9; i++)
    for (int j = 0; j <= 28; j++)
      p.push_back((vector<int>){i * j % 29 + 1, i * (j + 1) % 29 + 1, 30});
  
  // Remove specific vectors to avoid overlap and redundancy
  p.erase(find(p.begin(), p.end(), (vector<int>){1, 2, 30})),
      p.erase(find(p.begin(), p.end(), (vector<int>){3, 4, 30})),
      p.erase(find(p.begin(), p.end(), (vector<int>){5, 6, 30}));
  
  // Add some fixed three-element vectors
  p.push_back((vector<int>){1, 2, 3});
  p.push_back((vector<int>){4, 5, 6});

  // Add a number of structured triplets for additional coverage
  for (int i = 0; i <= 2; i++)
    for (int j = i; j <= i + 3; j++)
      for (int k = 0; k < 10; k++)
        p.push_back((vector<int>){k + 1, 11 + (k + i) % 10, 21 + (k + j) % 10});
  
  // Sort each pattern in p and create mapping from vector to index
  for (int i = 1; i <= 846; i++)
    sort(p[i].begin(), p[i].end()), id[p[i]] = i;
  
  cin >> t;
  while (t--) {
    cin >> n;
    
    // Store indices of patterns that contain each number (from 1 to n)
    vector<int> q[35]; 
    // Store positions used in each query by type
    vector<int> pos[850];
    
    // For each pattern in p, add its indices to respective element groupings
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < p[i].size(); j++)
        q[p[i][j]].push_back(i);
    
    // Process the first min(30,n) queries
    for (int i = 1; i <= min(30, n); i++) {
      cout << (i == 30 ? 3 : 1) << ' ' << q[i].size() << ' '; 
      for (int j = 0; j < q[i].size(); j++)
        cout << q[i][j] << (j == q[i].size() - 1 ? '\n' : ' ');
      fflush(stdout);
      
      int t;
      // Read the response to determine patterns used
      for (int j = 0; j < q[i].size(); j++) {
        cin >> t, pos[t].push_back(i);
      }
    }

    // Map positions back to original indices using mapping id[]
    for (int i = 1; i <= n; i++)
      a[id[pos[i]]] = i;

    // Output the final reconstructed permutation
    cout << "! ";
    for (int i = 1; i <= n; i++)
      cout << a[i] << (i == n ? '\n' : ' ');
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/