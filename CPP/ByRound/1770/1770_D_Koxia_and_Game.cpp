// Problem: CF 1770 D - Koxia and Game
// https://codeforces.com/contest/1770/problem/D

/*
Purpose: This code solves the problem of counting the number of valid arrays `c` such that Koxia wins the game.
         The game involves rounds where Koxia removes one element from a multiset {a[i], b[i], c[i]}, and Mahiru chooses
         one of the remaining two elements. Koxia wins if the sequence of Mahiru's choices forms a permutation of [1..n].
         The approach uses Union-Find (Disjoint Set Union) to group elements and track constraints on valid values for `c`.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) to manage groups of elements
- Modular arithmetic with modulo 998244353
- Greedy logic combined with constraint checking to determine valid choices for c[i]

Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (nlogn effectively)
Space Complexity: O(n) for the Union-Find structure and auxiliary arrays

*/

#include <string.h>
#include <iostream>

#define ll long long
using namespace std;

const int mxn = 1e5 + 5;
int fa[mxn], n, a[mxn], b[mxn], cnt[mxn]; // fa: Union-Find parent array, cnt: count of elements in each group

// Find function with path compression
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

const ll M = 998244353;

int main() {
  int T;
  cin >> T;
  for (; T--;) {
    // Initialize Union-Find
    for (int i = 0; i < mxn; ++i)
      fa[i] = i;
    memset(cnt, 0, sizeof(cnt)); // Reset count array
    
    cin >> n;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    for (int i = 1; i <= n; ++i)
      cin >> b[i];
      
    ll ans = 1; // Initial answer (number of valid c arrays)
    
    // Iterate through all rounds (elements of arrays a and b)
    for (int i = 1; i <= n; ++i) {
      int x = find(a[i]), y = find(b[i]); // Find root of a[i] and b[i]
      
      if (x != y) {
        // Merge two sets
        fa[x] = y;
        cnt[y] += cnt[x]; // Update count of root y
        // If root y already has more than one element in it, it's invalid
        if (cnt[y] > 1)
          ans *= 0; // No valid choices anymore
      } else {
        // Same set; check whether this is an invalid situation
        if (cnt[y] > 0) {
          ans *= 0; // Conflict detected
          continue;
        }
        // If a[i] == b[i], we can choose any of the n values for c[i]
        if (a[i] == b[i])
          (ans *= n) %= M;
        else
          // If a[i] != b[i], then c[i] must be one of two values (a[i], b[i]) -> 2 choices
          (ans *= 2) %= M;
        ++cnt[y]; // Increment count for root y
      }
    }
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/