// Problem: CF 1099 D - Sum in the tree
// https://codeforces.com/contest/1099/problem/D

/*
D. Sum in the tree
Algorithms/Techniques: Tree traversal, greedy assignment, min heap simulation
Time Complexity: O(n)
Space Complexity: O(n)

Mitya has a rooted tree with n vertices indexed from 1 to n, where the root has index 1.
Each vertex v initially had an integer number a_v >= 0 written on it.
For every vertex v Mitya has computed s_v: the sum of all values written on the vertices
on the path from vertex v to the root, as well as h_v — the depth of vertex v,
which denotes the number of vertices on the path from vertex v to the root.
Clearly, s_1=a_1 and h_1=1.
Then Mitya erased all numbers a_v, and by accident he also erased all values s_v
for vertices with even depth (vertices with even h_v). Your task is to restore
the values a_v for every vertex, or determine that Mitya made a mistake.
In case there are multiple ways to restore the values, you're required to find one
which minimizes the total sum of values a_v for all vertices in the tree.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
ll n, p[100005], s[100005], ans = 0, i;

int main() {
  scanf("%lld", &n);
  for (i = 2; i <= n; i++)
    scanf("%lld", &p[i]); // Read parent of each node
  for (i = 1; i <= n; i++)
    scanf("%lld", &s[i]); // Read sum values for each node
  for (i = 1; i <= n; i++)
    if (s[i] == -1)
      s[i] = 1e9 + 1; // Replace -1 with large number to indicate missing values
  for (i = 2; i <= n; i++)
    s[p[i]] = min(s[i], s[p[i]]); // Propagate minimum sum up the tree
  for (i = 1; i <= n; i++) {
    if (s[i] < s[p[i]]) { // Check if current node's sum is less than parent
      cout << -1 << endl;
      return 0;
    }
    if (s[i] <= 1e9) // If the value was not erased
      ans += s[i] - s[p[i]]; // Add difference as contribution to total cost
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/