// Problem: CF 707 B - Bakery
// https://codeforces.com/contest/707/problem/B

/*
Code Purpose:
This code finds the minimum cost for Masha to open a bakery in a city (not containing a storage) and connect it to the nearest storage via roads. 
It uses a graph representation with adjacency lists and checks for direct connections between storage cities and non-storage cities to find minimum edge weight.

Algorithms/Techniques:
- Graph traversal using adjacency list representation
- Brute-force search for minimum edge weight connecting storage and non-storage cities
- Use of map to track cities with storages for fast lookup

Time Complexity: O(n + m + k * d) where d is the maximum degree of any node (in worst case O(n))
Space Complexity: O(n + m) for adjacency list and map storage
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

// Structure to represent an edge in the graph
struct edge {
  ll to, cost;
  edge(ll a, ll b) {
    to = a;
    cost = b;
  }
};

// Adjacency list representation of the graph
vector<edge> adj[100010];

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie();
  ll i, j, k;
  ll n, m;
  ll u, v, w;
  
  // Read number of cities, roads and storages
  cin >> n >> m >> k;
  
  // Read all the edges and build adjacency list
  for (i = 0; i < m; i++) {
    cin >> u >> v >> w;
    adj[u].push_back(edge(v, w));
    adj[v].push_back(edge(u, w));
  }
  
  // If there are no storages, return -1
  if (k == 0) {
    printf("-1");
    return 0;
  }
  
  // Map to track which cities contain storages
  map<ll, bool> mp;
  for (i = 0; i < k; i++) {
    cin >> j;
    mp[j] = 1;
  }
  
  // Find minimum edge weight connecting storage to non-storage city
  ll min = inf;
  for (i = 1; i <= n; i++) {
    // If current city is a storage city and has connections
    if (mp[i] == 1 && adj[i].size() > 0) {
      for (j = 0; j < adj[i].size(); j++) {
        // Check if adjacent city is not a storage city and if edge cost is smaller
        if (mp[adj[i][j].to] == 0 && adj[i][j].cost < min) {
          min = adj[i][j].cost;
        }
      }
    }
  }
  
  // Output the minimum cost or -1 if not possible
  if (min != inf)
    printf("%I64d", min);
  else
    printf("-1");
    
  cin.clear();
  cin.ignore();
  cin.get();
  return 0;
}


// https://github.com/VaHiX/CodeForces/