// Problem: CF 761 B - Dasha and friends
// https://codeforces.com/contest/761/problem/B

/*
Purpose: Determine if two sequences of barrier positions, representing runs by
Kefa and Sasha on a circular track, correspond to the same track but with
different starting points.

Algorithm:
- The core idea is to compute the "gaps" between consecutive barriers for each
runner.
- For a circular track, we also account for the gap from the last barrier back
to the first.
- Since the starting point can differ, we check all possible rotations of
Sasha's gap sequence against Kefa's.
- If any rotation matches, the tracks are the same; otherwise, they are
different.

Time Complexity: O(n^2)
Space Complexity: O(n)

Techniques:
- Use queues to store the gap sequences.
- Simulate rotation by popping and pushing elements.
*/

#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <stdio.h>

typedef long long int ll;
#define pp pair<ll, ll>
#define ppp pair<ll, pp>
#define dbg printf("x");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  int i, j, k;
  int n, l;
  cin >> n >> l;
  int a[n], b[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  for (i = 0; i < n; i++)
    cin >> b[i];
  queue<int> ds; // queue for Sasha's gaps
  queue<int> kf; // queue for Kefa's gaps
  for (i = 1; i < n; i++) {
    ds.push(a[i] - a[i - 1]); // compute gaps between barriers for Kefa
  }
  ds.push(l - a[n - 1] + a[0]); // add the wrap-around gap for Kefa
  for (i = 1; i < n; i++) {
    kf.push(b[i] - b[i - 1]); // compute gaps between barriers for Sasha
  }
  kf.push(l - b[n - 1] + b[0]); // add the wrap-around gap for Sasha
  while (n) {                   // try all rotations of Sasha's sequence
    if (ds == kf) {             // if current rotation matches Kefa's sequence
      cout << "YES";
      return 0;
    }
    i = ds.front(); // get the front element
    ds.pop();       // remove it from front
    ds.push(i);     // push it to the back (simulate rotation)
    n--;            // reduce rotation count
  }
  cout << "NO"; // no rotation matched
  return 0;
}

// https://github.com/VaHiX/CodeForces/