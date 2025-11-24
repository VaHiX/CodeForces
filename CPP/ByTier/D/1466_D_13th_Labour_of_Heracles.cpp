// Problem: CF 1466 D - 13th Labour of Heracles
// https://codeforces.com/contest/1466/problem/D

/*
D. 13th Labour of Heracles

Purpose:
This code solves a problem involving coloring edges of a tree to maximize the sum of values of connected components in each color class.
It uses a greedy approach where:
- In each step k, we want to assign k colors to edges to maximize total value.
- Greedily, at each step k, we try to take the largest possible sum of weights in a component and assign it to one of k color groups.
- The optimal assignment of edges is done by considering each edge being the "cut" that separates the tree into two parts, and choosing from either part the one with maximum weight sum.

Algorithms:
- Tree traversal using adjacent lists representation
- Greedy selection from multiset to always pick highest weighted component
- Multiset for maintaining candidate weights efficiently

Time Complexity: O(n log n) per test case
Space Complexity: O(n) per test case

*/
#include <cstdio>
#include <set>
#include <vector>
#include <iterator>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> w(n);
    ll res(0); // total weight sum, initial result
    std::vector<bool> d(n, 0); // visited nodes flag
    std::multiset<ll> s; // multiset to store weights of components (greedy selection)
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &w[p]);
      res += w[p]; // accumulate total vertex weight
    }
    for (ll p = 1; p < n; p++) {
      ll x, y;
      scanf("%lld %lld", &x, &y);
      --x;
      --y;
      // If either of the nodes was already visited before inserting an edge,
      // it means one side of this new edge has been included in a component
      if (d[x]) {
        s.insert(w[x]); // add weight to candidate set
      }
      if (d[y]) {
        s.insert(w[y]); // add weight to candidate set
      }
      d[x] = 1; // mark nodes as visited when an edge involving them is processed
      d[y] = 1;
    }
    printf("%lld ", res); // print base case: full tree with one color
    for (ll p = 2; p < n; p++) {
      std::multiset<ll>::reverse_iterator it = s.rbegin(); // get largest element
      res += *it; // add the max component weight to sum
      s.erase(s.find(*it)); // remove the used maximum element
      printf("%lld ", res); // output updated result
    }
    puts(""); // newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/