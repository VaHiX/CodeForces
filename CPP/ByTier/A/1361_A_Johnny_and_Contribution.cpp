// Problem: CF 1361 A - Johnny and Contribution
// https://codeforces.com/contest/1361/problem/A

/*
 * Problem: Johnny and Contribution
 * Algorithm: Graph traversal with topological ordering simulation
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 *
 * This code determines the order in which Johnny should write his blogs
 * such that when he follows his greedy strategy of choosing the smallest
 * available topic number based on already written neighbors, it matches
 * the desired topic assignment.
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
#define mst(a) memset(a, 0, sizeof a)
int num[N], n, m;
vector<int> e[N], ans, col[N];

int main() {
  scanf("%d%d", &n, &m);
  // Read edges and build adjacency list
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  
  // Assign each blog to its desired topic group
  for (int i = 1; i <= n; i++) {
    int c;
    scanf("%d", &c);
    col[c].push_back(i);
    num[i] = 1;  // Initialize number of neighbors with same topic
  }
  
  // Process blogs in order of topics (1 to n)
  for (int i = 1; i <= n; i++) {
    for (auto u : col[i]) {  // For each blog with topic i
      // If the current blog has already been processed (this should not happen)
      if (num[u] != i)
        puts("-1"), exit(0);
      
      // Increment count for neighbors that have the same topic as current blog
      for (auto v : e[u])
        if (num[v] == i)
          num[v]++;
          
      ans.push_back(u);  // Add current blog to result order
    }
  }
  
  // Output the processing order
  for (auto i : ans)
    printf("%d ", i);
    
  return 0;
}


// https://github.com/VaHiX/codeForces/