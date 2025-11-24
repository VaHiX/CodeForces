// Problem: CF 1852 B - Imbalanced Arrays
// https://codeforces.com/contest/1852/problem/B

/*
Code Purpose:
This program determines whether an imbalanced array can be constructed from a given array of non-negative integers.
An imbalanced array b satisfies the following conditions:
1. Each element b[i] is in the range [-n, n] and is not zero.
2. No two elements in b sum to zero.
3. For each i, exactly a[i] elements j exist such that b[i] + b[j] > 0.

Algorithm:
The approach uses sorting and a two-pointer technique to assign values to the result array.
We sort the input array a in ascending order and process the elements in decreasing order using two pointers.
We assign positive values to elements that require fewer positive sums, and negative values to those requiring more.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the input and result arrays
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

using namespace std;
pair<int, int> p[100005]; // Store value and index pairs
int res[100005]; // Result array to store the imbalanced array

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i].first);
      p[i].second = i;
    }
    sort(p, p + n); // Sort by the values of a[i]
    int l = 0, r = n - 1;
    bool ok = true;
    while (l <= r) {
      // Check if current right element can be placed with a positive value
      if (n - p[r].first == l) {
        res[p[r--].second] = r - l + 1;
      } 
      // Check if current left element can be placed with a negative value
      else if (p[l].first == n - r - 1) {
        res[p[l++].second] = -(r - l + 1);
      } 
      // If neither condition is met, impossible to construct
      else {
        ok = false;
        break;
      }
    }
    if (!ok) {
      printf("NO\n");
    } else {
      printf("YES\n");
      for (int i = 0; i < n; ++i)
        printf("%d ", res[i]);
      printf("\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/