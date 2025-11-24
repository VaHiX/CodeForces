// Problem: CF 1693 B - Fake Plastic Trees
// https://codeforces.com/contest/1693/problem/B

/*
Purpose: 
This code solves the problem of finding the minimum number of operations to set values on vertices of a tree such that each vertex v has a value between l[v] and r[v]. Each operation allows selecting a vertex v and adding a non-decreasing array of non-negative integers to all vertices on the path from root to v.

Algorithm:
- We process nodes in reverse topological order (from leaves to root)
- For each node, we compute how much we need to add to satisfy the constraints
- The key idea is to use a difference array approach on the tree where we propagate the required increments up the tree
- We count how many operations are needed by checking if the current node's excess (d[i]) is less than l[i]

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing parent info, ranges, and difference array

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
#define ll long long
int n, p[200100], ans;
ll l[200100], r[201000], d[200100];

void sol() {
  ans = 0;
  scanf("%d", &n);
  for (int i = 2; i <= n; i++)
    scanf("%d", &p[i]);  // Read parent of each node
  for (int i = 1; i <= n; i++)
    scanf("%lld%lld", &l[i], &r[i]), d[i] = 0;  // Read ranges and initialize diff array
  
  for (int i = n; i; i--) {  // Process nodes in reverse order (leaf to root)
    if (d[i] < l[i]) {  // If current increment is not enough to satisfy lower bound
      d[i] = r[i];  // Set to upper bound (as it's the maximum we allow)
      ans++;  // Increment operation count
    }
    d[i] = min(d[i], r[i]);  // Ensure we don't exceed the upper bound
    
    if (i > 1)  // If not the root
      d[p[i]] += d[i];  // Propagate the increment to parent
  }
  
  printf("%d\n", ans);  // Output result
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/