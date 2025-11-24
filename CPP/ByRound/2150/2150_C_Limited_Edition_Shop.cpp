// Problem: CF 2150 C - Limited Edition Shop
// https://codeforces.com/contest/2150/problem/C

/*
Problem: C. Limited Edition Shop
Algorithms/Techniques: Segment Tree with Lazy Propagation, Dynamic Programming, Greedy

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for the segment tree and auxiliary arrays

Description:
This problem involves finding the maximum sum of values according to you over all possible sets of objects that Alice could have bought.
We use a segment tree with lazy propagation to efficiently maintain and query information about the best value achievable up to a certain position,
and update the current state after each purchase.

*/
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;
const int kMaxN = 2e5 + 2;

struct V {
  LL a, mx; // 'a' for lazy propagation, 'mx' for maximum value in segment
} v[kMaxN * 8];
LL a[kMaxN], b[kMaxN], w[kMaxN], t, n;

// Add value to node and propagate to children
void Add(int i, LL val) { 
  v[i].a += val, v[i].mx += val; 
}

// Push lazy values down to children
void Push(int i) {
  if (v[i].a) {
    Add(i << 1, v[i].a), Add(i << 1 | 1, v[i].a); // Propagate to left and right children
    v[i].a = 0;
  }
}

// Update max value in node based on children
void Pull(int i) { 
  v[i].mx = max(v[i << 1].mx, v[i << 1 | 1].mx); 
}

// Range update: add value to range [tl, tr] in segment tree
void Plus(int i, int l, int r, int tl, int tr, LL val) {
  if (tl <= l && r <= tr) {
    Add(i, val);
    return;
  }
  Push(i); // Propagate lazy updates before proceeding
  int m = l + r >> 1; // Midpoint of current range
  if (tl <= m) {
    Plus(i << 1, l, m, tl, tr, val); // Process left subtree
  }
  if (tr > m) {
    Plus(i << 1 | 1, m + 1, r, tl, tr, val); // Process right subtree
  }
  Pull(i);
}

// Point update: set value at position 'tar' in segment tree
void Update(int i, int l, int r, int tar, LL val) {
  if (l == r) {
    v[i].mx = v[i].a = max(v[i].a, val); // Set maximum value at the leaf
    return;
  }
  Push(i); // Propagate lazy updates
  int m = l + r >> 1;
  tar <= m ? Update(i << 1, l, m, tar, val)
           : Update(i << 1 | 1, m + 1, r, tar, val);
  Pull(i);
}

// Range query: find maximum value in range [tl, tr]
LL Query(int i, int l, int r, int tl, int tr) {
  if (tl <= l && r <= tr) {
    return v[i].mx;
  }
  Push(i); // Propagate lazy updates before querying
  int m = l + r >> 1;
  LL res;
  if (tl <= m && tr > m) {
    // Both left and right segments are queried
    res = max(Query(i << 1, l, m, tl, tr), Query(i << 1 | 1, m + 1, r, tl, tr));
  } else {
    // Only one side is queried
    res = tr <= m ? Query(i << 1, l, m, tl, tr)
                  : Query(i << 1 | 1, m + 1, r, tl, tr);
  }
  Pull(i);
  return res;
}

// Build the segment tree with initial values
void Build(int i, int l, int r) {
  if (l == r) {
    v[i].a = v[i].mx = l ? -1e18 : 0; // Initialize root as 0, others as -INF
    return;
  }
  v[i].a = 0;
  int m = l + r >> 1;
  Build(i << 1, l, m), Build(i << 1 | 1, m + 1, r);
  Pull(i);
}

int main() {
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> w[i]; // Object values
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[i]; // Alice's preference order
    }
    for (int i = 1, x; i <= n; i++) {
      cin >> x;
      b[x] = i; // Bob's preference mapped to positions (b[i] = position of object i in Bob's list)
    }
    Build(1, 0, n); // Initialize segment tree
    Update(1, 0, n, 0, 0); // Initialize first element with value 0
    
    for (int i = 1; i <= n; i++) {
      LL x = b[a[i]]; // Position of Alice's preferred object in Bob's list
      LL mx = Query(1, 0, n, 0, x); // Get max value before position x
      Plus(1, 0, n, 0, x, w[a[i]]); // Add the value to all nodes up to position x
      Update(1, 0, n, x, mx); // Update current position with new max value
    }
    
    cout << v[1].mx << '\n'; // Output the maximum sum achievable
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/