// Problem: CF 1819 B - The Butcher
// https://codeforces.com/contest/1819/problem/B

/*
 * Problem: The Butcher
 * Algorithm:
 *   - Given n rectangles, determine all possible (h, w) pairs such that
 *     the rectangles can be obtained by a sequence of cuts from a single
 *     initial rectangle of size h x w.
 *   - For each candidate (h, w), simulate the reverse process:
 *     - Start with rectangle (h, w)
 *     - At each step, try to find a rectangle that was cut from the current one
 *     - If all rectangles are matched and accounted for, it's valid.
 *   - Use a greedy approach to try matching rectangles based on their width or
 * height, storing indices of rectangles in buckets by their dimensions.
 *   - The key is to check both orientations: (h,w) and (w,h) as potential
 * starting sizes.
 *
 * Time Complexity: O(n^2) in worst case for checking, but due to optimization
 * with buckets and limited dimension sizes, it's often much better in practice.
 * Space Complexity: O(n + max_dimension) for storage of rectangles and buckets.
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <stdio.h>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> llll;
const int Maxn = 200005;
const int Maxm = 1000005;
int T;
int n;
ll S;
int a[Maxn], b[Maxn];
bool tk[Maxn];
vector<int> seqA[Maxm], seqB[Maxm];

// Function to check if a given (A, B) rectangle can produce all given
// rectangles
bool Check(ll A, ll B) {
  // Mark all rectangles as unprocessed
  fill(tk, tk + n, false);
  // Initialize buckets (seqA, seqB) to store indices of rectangles based on
  // their dimensions
  for (int i = 0; i < n; i++) {
    seqA[a[i]].push_back(i);
    seqB[b[i]].push_back(i);
  }
  // Simulate reverse cutting process
  while (A > 0 && B > 0) {
    // Try to match a rectangle based on height A
    if (A < Maxm && !seqA[A].empty()) {
      int ind = seqA[A].back();
      seqA[A].pop_back();
      if (!tk[ind]) {
        tk[ind] = true;
        B -= b[ind]; // Reduce B by the width of removed rectangle
      }
      continue;
    }
    // Try to match a rectangle based on width B
    if (B < Maxm && !seqB[B].empty()) {
      int ind = seqB[B].back();
      seqB[B].pop_back();
      if (!tk[ind]) {
        tk[ind] = true;
        A -= a[ind]; // Reduce A by the height of removed rectangle
      }
      continue;
    }
    // If no match found, return false
    return false;
  }
  // If process was successful, all rectangles were matched
  return true;
}

// Function to clear buckets
void Empty() {
  for (int i = 0; i < n; i++) {
    seqA[a[i]].clear();
    seqB[b[i]].clear();
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    S = 0;
    int mxa = 0, mxb = 0;
    // Read rectangles, compute total area and find maximum dimensions
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &a[i], &b[i]);
      S += ll(a[i]) * b[i];
      mxa = max(mxa, a[i]);
      mxb = max(mxb, b[i]);
    }
    set<llll> St;
    // Try checking if (mxa, S/mxa) works as starting rectangle
    if (S % mxa == 0 && Check(mxa, S / mxa)) {
      St.insert(llll(mxa, S / mxa));
    }
    Empty();
    // Try checking if (S/mxb, mxb) works as starting rectangle
    if (S % mxb == 0 && Check(S / mxb, mxb)) {
      St.insert(llll(S / mxb, mxb));
    }
    Empty();
    // Output valid pairs
    printf("%d\n", int(St.size()));
    for (auto el : St)
      cout << el.first << ' ' << el.second << '\n';
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/