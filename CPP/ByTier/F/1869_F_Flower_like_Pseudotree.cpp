// Problem: CF 1869 F - Flower-like Pseudotree
// https://codeforces.com/contest/1869/problem/F

/* 
 * Flower-like Pseudotree Construction
 * 
 * Problem: Given vertex degrees, construct a flower-like pseudotree.
 * 
 * A flower-like pseudotree is a connected graph with exactly one cycle and no self-loops, 
 * such that after removing the cycle edges, the resulting forest has all trees with 
 * equal depth when rooted at their corresponding cycle vertex.
 * 
 * Key Observations:
 * - A pseudotree with n vertices has exactly n edges.
 * - The total degree sum must be 2 * n for a valid pseudotree.
 * - For a flower-like pseudotree, certain conditions involving vertex degrees determine 
 *   if construction is possible.
 * 
 * Algorithm:
 * 1. Preprocess degrees and sort them.
 * 2. Classify vertices into degrees 1, 2, and others.
 * 3. Use different strategies to build the structure based on these classifications.
 * 4. For valid constructions, connect leaves and build cycles appropriately to ensure
 *    flower-like property.
 * 
 * Time Complexity: O(n log n) - due to sorting and linear processing
 * Space Complexity: O(n) - for storing degrees and edges
 */
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>

using namespace std;
const int N = 1e6 + 10;
int n;
pair<int, int> d[N];
void connect(int a, int b) {
  // Output an edge between vertices a and b (based on their indices)
  printf("%d %d\n", d[a].second, d[b].second);
  d[a].first--;
  d[b].first--;
}
void createCycle(int start, int end) {
  // Create a cycle from start to end vertices (indices)
  for (int i = start; i < end; i++) {
    connect(i, i + 1);
  }
  connect(end, start);
}
void solveLeaves(int totalLeaves) {
  // Connect leaves to the cycle, ensuring each has appropriate degree
  for (int i = 0, j = totalLeaves; i < totalLeaves; i++) {
    while (d[j].first == 0)
      j++;
    connect(i, j);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int cases;
  scanf("%d", &cases);
  while (cases--) {
    scanf("%d", &n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &d[i].first);
      d[i].second = i + 1;
      sum += d[i].first;
    }
    sort(d, d + n); // Sort vertices by degree to group them efficiently
    
    int ones = 0, twos = 0;
    while (ones < n && d[ones].first == 1)
      ones++;
    while (ones + twos < n && d[ones + twos].first == 2)
      twos++;
    int left = n - ones - twos; // Count of vertices with degree >= 3
    
    if (sum != 2 * n || left == 1) {
      // Check for basic validitiy:
      // 1. Total degree sum must equal 2 * n
      // 2. If there's only one vertex with degree >= 3, cannot form valid flower-like pseudotree
      printf("No\n");
    } else if (ones == 0 || twos == 0) {
      // If there are no vertices of degree 1 or 2, construct simple cycle with leaves
      printf("Yes\n");
      createCycle(ones, n - 1);
      solveLeaves(ones);
    } else if ((left + twos) % 2 == 0) {
      // If the combined count of higher-degree vertices and 2s is even
      printf("Yes\n");
      createCycle(n - 2, n - 1);
      int nxt = n - 1, nxtnxt = n - 2;
      for (int i = n - 3; i >= ones; i--) {
        connect(i, nxt);
        nxt = nxtnxt;
        nxtnxt = i;
      }
      solveLeaves(ones);
    } else if (twos + left < 5) {
      // Not enough vertices to form a valid structure
      printf("No\n");
    } else if (d[n - 1].first >= 4) {
      // If the highest degree is at least 4
      printf("Yes\n");
      createCycle(n - 2, n - 1);
      int nxt = n - 1, nxtnxt = n - 2;
      connect(n - 3, n - 1);
      for (int i = n - 4; i >= ones; i--) {
        connect(i, nxt);
        nxt = nxtnxt;
        nxtnxt = i;
      }
      solveLeaves(ones);
    } else if (left >= 3 && left + twos >= 7) {
      // If at least 3 vertices have degree >= 3 and total >= 7
      printf("Yes\n");
      createCycle(n - 2, n - 1);
      connect(n - 3, n - 1);
      connect(n - 4, n - 2);
      connect(n - 5, n - 3);
      int nxt = n - 3, nxtnxt = n - 4;
      for (int i = n - 6; i >= ones; i--) {
        connect(i, nxt);
        nxt = nxtnxt;
        nxtnxt = i;
      }
      solveLeaves(ones);
    } else {
      // If no condition applies, construction is impossible
      printf("No\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/