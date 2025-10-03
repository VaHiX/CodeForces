// Problem: CF 2118 F - Shifts and Swaps
// https://codeforces.com/contest/2118/problem/F

/*
F. Shifts and Swaps
time limit per test6 seconds
memory limit per test512 megabytes

Algorithms/Techniques:
- Graph representation using map for tree isomorphism checking
- Cyclic shift equivalence handling via rotation
- Tree serialization with DFS traversal
- String rotation comparison using KMP-like approach

Time Complexity: O(n * m + sum of n over all test cases)
Space Complexity: O(n * m)

The solution constructs a rooted tree for each array based on element ordering,
serializes the trees, and compares if the serialized representations are equal
after accounting for cyclic shifts.
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;
int n, m, hid;
map<pair<int, vector<int>>, int> mp; // Map to store unique tree serializations

// Function to convert array into a tree structure and serialize it
vector<int> get_graph(vector<int> arr) {
  vector<vector<int>> g(n); // Adjacency list for the constructed graph
  vector<int> roots;        // Root nodes of trees (elements with value 1)
  vector<int> las(m + 1);   // Last occurrence index of each element
  for (int i = 0; i < n; i++)
    las[arr[i]] = i; // Initialize last seen indices

  for (int i = 0; i < n; i++) {
    if (arr[i] == 1) {
      roots.push_back(i); // Mark root node
    } else {
      int l = max(las[arr[i] - 1], las[arr[i]]); // Find parent position
      g[l % n].push_back(i);  // Connect child to parent
    }
    las[arr[i]] = i + n;  // Update last seen index (extended beyond current array)
  }

  vector<int> sec; // Vector to store serialized tree data

  // Lambda for recursive DFS traversal and serialization
  auto get_mp = [&](auto self, int x) -> int {
    vector<int> ch; // Child serializations
    for (auto e : g[x])
      ch.push_back(self(self, e)); // Recursively get child serializations
    
    sort(ch.begin(), ch.end()); // Sort children to normalize order

    auto &v = mp[{arr[x], ch}]; // Look up or assign ID based on node and children
    if (v == 0) v = ++hid; // Assign new ID if not present
    return v;
  };

  for (auto e : roots) {
    sec.push_back(get_mp(get_mp, e)); // Serialize each root tree
  }

  // Rotate to smallest lexicographical version to account for rotation
  int k = 0, i = 0, j = 1, n = sec.size();
  while (k < n && i < n && j < n) {
    if (sec[(i + k) % n] == sec[(j + k) % n]) {
      k++;
    } else {
      sec[(i + k) % n] > sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
      if (i == j) i++;
      k = 0;
    }
  }

  i = min(i, j); // Choose starting point that minimizes rotation
  rotate(sec.begin(), sec.begin() + i, sec.end()); // Perform rotation

  return sec; // Return normalized serial form of tree
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    hid = 0;
    mp.clear(); 
    scanf("%d%d", &n, &m);
    vector<int> a, b;
    for (int i = 0, x; i < n; i++)
      scanf("%d", &x), a.push_back(x); // Read first array
    for (int i = 0, x; i < n; i++)
      scanf("%d", &x), b.push_back(x); // Read second array

    vector<int> A = get_graph(a), B = get_graph(b); // Serialize both arrays
    if (A == B)
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/