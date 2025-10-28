// Problem: CF 2064 E - Mycraft Sand Sort
// https://codeforces.com/contest/2064/problem/E

/*
E. Mycraft Sand Sort
Algorithms/Techniques: Union-Find (Disjoint Set Union), Simulation of Gravity Sorting Process

Time Complexity: O(n * α(n)) per test case, where α is the inverse Ackermann function (practically constant)
Space Complexity: O(n)

This code simulates a gravity sort process on a permutation p with colored sand blocks.
The task is to count how many different pairs (p', c') can produce the exact same layout after gravity sorting.
We reverse-engineer the process using union-find to group consecutive elements of same color,
then simulate removal of elements in order of their original positions to compute possible arrangements.

The idea:
- We model a linked list with left and right pointers to simulate a sequence of indices.
- Using Union-Find, we group segments that have the same color and are adjacent.
- When elements are "removed", we check if merging of groups is needed due to adjacent elements having same color.
- This allows us to count valid permutations that result in same sand layout by tracking how many positions
  can potentially be arranged with remaining available choices.

*/

#include <iostream>

using namespace std;
typedef long long ll;
#define M 998244353
#define N 400000

int i, j, k, n, m, T, c[N + 50], pos[N + 50], l[N + 50], r[N + 50], sz[N + 50],
    fa[N + 50];
ll res;

// Find root of x with path compression
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

// Process removing element at position x (update result and structure)
void fuck(int x) {
  int j, k = find(x);
  res = res * sz[k] % M;  // Multiply by number of elements in the group
  sz[k]--;
  r[l[x]] = r[x];        // Remove element from linked list
  l[r[x]] = l[x];
  if (!sz[k]) {
    j = l[x];
    k = r[x];
    if (c[j] == c[k]) {           // If adjacent elements have same color
      j = find(j);
      k = find(k);
      fa[k] = j;                  // Merge groups
      sz[j] += sz[k];             // Update size of merged group
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    c[n + 1] = 0;                  // Sentinel for easier handling
    
    // Initialize left/right pointers and other data structures
    for (i = 1; i <= n; i++) {
      cin >> k;
      pos[k] = i;                  // Position of value k in original array
      l[i] = i - 1;
      r[i] = i + 1;
      fa[i] = i;
      sz[i] = 1;
    }
    
    for (i = 1; i <= n; i++)
      cin >> c[i];                 // Read color array

    // Union all adjacent elements with same color
    for (i = 2; i <= n; i++)
      if (c[i] == c[i - 1]) {
        fa[i] = find(i - 1);
        sz[find(i)]++;
      }

    res = 1;
    
    // Process in reverse order of positions in permutation
    for (i = 1; i <= n; i++)
      fuck(pos[i]);
      
    cout << res << '\n';
  }
}


// https://github.com/VaHiX/codeForces/