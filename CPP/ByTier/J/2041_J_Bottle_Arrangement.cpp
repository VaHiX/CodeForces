// Problem: CF 2041 J - Bottle Arrangement
// https://codeforces.com/contest/2041/problem/J

/*
J. Bottle Arrangement
Algorithms/Techniques: 
Monotonic stack for finding next smaller elements, recursion with memoization for checking valid mountain arrangements.
Time Complexity: O(n log n) due to sorting and processing with monotonic stack.
Space Complexity: O(n) for arrays and recursion stack.

Given two rows of bottles, place the front row to form a mountain-shaped sequence,
where each bottle in front is strictly shorter than the corresponding one below.
Caps can be removed from front bottles (reducing height by 1), and we want to
minimize total caps removed.
*/

#include <algorithm>
#include <iostream>

#define M 500010
using namespace std;
int n, a[M], b[M], l[M], r[M], s[M], k, d;

// Function to calculate minimum caps needed using recursion and memoization
int pd(int p, int x, int y) {
  if (x > y)
    return 0;
  int d = 1e6; // Initialize with infinity-like value
  // If back bottle can be blocked by current front bottle from left
  if (b[n - p + x] <= a[p])
    d = min(d, pd(l[p], x, p - 1) + (b[n - p + x] == a[p]));
  // If back bottle can be blocked by current front bottle from right
  if (b[n - y + p] <= a[p])
    d = min(d, pd(r[p], p + 1, y) + (b[n - y + p] == a[p]));
  return d;
}

int main() {
  std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  
  // Build monotonic stack to find next smaller elements on both sides
  for (register int i = 1; i <= n; i++) {
    cin >> a[i];
    d = 0;
    while (k && a[s[k]] >= a[i]) {
      d = s[k];
      --k;
    }
    if (k)
      r[s[k]] = i;
    l[i] = d, s[++k] = i;
  }
  
  // Read front row heights
  for (register int i = 1; i <= n; i++)
    cin >> b[i];
  sort(b + 1, b + n + 1); // Sort to enable greedy choice
	
  // Start recursive computation with root of the stack
  d = pd(s[1], 1, n);
  
  cout << (d == 1e6 ? -1 : d);
  return 0;
}


// https://github.com/VaHiX/codeForces/