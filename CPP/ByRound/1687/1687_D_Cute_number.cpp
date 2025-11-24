// Problem: CF 1687 D - Cute number
// https://codeforces.com/contest/1687/problem/D

/*
Algorithm: 
The problem involves finding the smallest non-negative integer `k` such that `a[i] + k` is a cute number for all elements in the array. A number is cute if it satisfies a specific condition based on the nearest square numbers.

Approach:
- Preprocess the array to compute the differences between consecutive elements.
- Use a sliding window technique with a linked list structure to maintain intervals.
- For each candidate `k`, check whether all `a[i] + k` are cute by examining the condition:
    - Let `g(x)` = max square ≤ x
    - Let `f(x)` = min square > x
    - x is cute if `x - g(x) < f(x) - x`

Time Complexity: O(n * sqrt(max_a)) where n is the size of array and max_a is the maximum element in array.
Space Complexity: O(n) for storing the array and auxiliary structures.

*/
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;
#define int long long
const int N = 2e6 + 1;
int n, a[N], h[N], t[N];
vector<int> mg[N];
signed main() {
  scanf("%lld", &n);
  for (int i = 0; i < n; ++i)
    scanf("%lld", &a[i]), h[i] = i - 1, t[i] = i + 1;
  for (int i = 1; i < n; ++i)
    mg[a[i] - a[i - 1]].push_back(i);
  for (int i = 0;; ++i) {
    for (int j : mg[i])
      t[h[j]] = t[j], h[t[j]] = h[j];
    int s = i * i - a[0], x = 0, y = s + i, j = i;
    for (int l = 0; l < n; l = t[l]) {
      while (j * (j + 1) < a[l] + s)
        ++j;
      x = max(x, j * j - a[l]), y = min(y, j * (j + 1) - a[t[l] - 1]);
    }
    if (x <= y) {
      printf("%lld", x);
      exit(0);
    }
  }
}


// https://github.com/VaHiX/CodeForces/