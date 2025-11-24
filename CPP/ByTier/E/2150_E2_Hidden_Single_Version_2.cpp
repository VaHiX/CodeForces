// Problem: CF 2150 E2 - Hidden Single (Version 2)
// https://codeforces.com/contest/2150/problem/E2

/*
E2. Hidden Single (Version 2)
Interactive problem to find the single element in an array where all elements from 1 to n appear twice except one.
Uses binary search with random subsets to isolate the unique element.

Algorithms/Techniques:
- Interactive binary search approach using subset queries
- Randomized partitioning of indices into two groups
- Query optimization to reduce number of calls

Time Complexity: O(n log n) — Each iteration reduces the search space by half, and we do at most log n iterations.
Space Complexity: O(n) — Storing vectors for subsets and current candidates.

*/
#include <stdio.h>
#include <algorithm>
#include <random>
#include <vector>

#define fo(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, l, r) for (int i = (l); i >= (r); --i)
#define fu(i, l, r) for (int i = (l); i < (r); ++i)
#define pi pair<int, int>
#define eb emplace_back
#define vi vector<int>
#define fi first
#define se second
#define ll long long
using namespace std;
mt19937 rnd(19491001);
const int N = 1007;
int n, p[N];

// Ask the interactor if element 'x' is present in subset S
int ask(vi S, int x) {
  printf("? %d %d ", x, (int)S.size());
  for (int i : S)
    printf("%d ", i);
  printf("\n");
  fflush(stdout);
  int z;
  scanf("%d", &z);
  return z;
}

void work() {
  scanf("%d", &n);
  if (n == 1) {
    printf("! %d\n", 1);
    fflush(stdout);
    return;
  }
  vi v;
  fo(i, 1, n) v.eb(i); // Initialize candidate list
  int ok = 0; // Flag to control initial partitioning logic
  while (v.size() > 1) {
    vi L, R; // Left and right subsets for comparison
    fo(i, 1, n + n - 1) p[i] = i; // Fill array with indices 1 to 2n-1
    shuffle(p + 1, p + n + n, rnd); // Shuffle to randomize partitioning
    fo(i, 1, n) L.eb(p[i]); // Assign first n indices to L
    fo(i, n + 1, n + n - 1) R.eb(p[i]); // Assign rest to R
    int c = n & 1; // Determine parity based on n
    vi wl, wr; // Lists for elements determined to be in L or R
    for (int x : v) { // For each candidate element
      if (ask(L, x)) { // If x is found in L
        if (!ask(R, x)) // If also not found in R, must be in L group
          wl.eb(x);
        else
          c ^= 1; // Otherwise, increment parity
      } else
        wr.eb(x); // If x not found in L, then it's in R
    }
    if (ok) {
      v = wl;
      for (int x : wr)
        v.eb(x);
    } else {
      ok = 1;
      if (c) // Based on parity check, choose which group to keep
        v = wl;
      else
        v = wr;
    }
  }
  printf("! %d\n", v[0]); // Output final unique element
  fflush(stdout);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    work();
}


// https://github.com/VaHiX/CodeForces/