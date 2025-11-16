// Problem: CF 1151 E - Number of Components
// https://codeforces.com/contest/1151/problem/E

/*
 * Problem: Number of Components in a Tree
 * 
 * Algorithm:
 * - The problem involves computing the sum of connected components over all subranges of vertex values.
 * - We use a mathematical approach to calculate contribution of each edge pair (i, i+1) in the tree.
 * - The key idea is to compute how many times a particular edge contributes to the total sum.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * The solution uses a formula derived from the principle of inclusion-exclusion:
 * - First, we compute the total contribution of each vertex.
 * - Then, we subtract the overcounted contributions from adjacent edges.
 * 
 * For a tree with vertices connected in series (1--2--3--...--n), 
 * each pair (i, i+1) contributes based on the minimum of their values.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;

int n, a[100010]; // Array to store vertex values, indexed from 1
long long ans; // Final answer

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    // Add contribution of vertex i to the answer
    // Each vertex contributes a[i] * (n - a[i] + 1) times
    ans += 1ll * a[i] * (n - a[i] + 1);
  }
  for (int i = 1; i < n; i++) {
    // Subtract overcounted contribution from adjacent vertices
    // This adjustment accounts for the components formed by edges between adjacent vertices
    ans -= 1ll * min(a[i], a[i + 1]) * (n - max(a[i], a[i + 1]) + 1);
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/