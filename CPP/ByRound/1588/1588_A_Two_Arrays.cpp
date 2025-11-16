// Problem: CF 1588 A - Two Arrays
// https://codeforces.com/contest/1588/problem/A

/*
Code Purpose:
This program determines whether it's possible to transform array 'a' into array 'b' using a specific operation:
- Choose a non-negative integer k (0 <= k <= n)
- Select k distinct indices and increment the values at those indices by 1
- Permute the elements of the array in any order
The key insight is that since we can permute the elements, the order doesn't matter, so we can sort both arrays and check:
1. If all elements in 'a' are equal to corresponding elements in 'b', then k = 0 transformation works.
2. If every element in 'a' is exactly 1 less than its corresponding element in 'b', then we can increment all elements of 'a' to match 'b'.
Otherwise, it's impossible.

Algorithms/Techniques:
- Sorting both arrays to ignore the permutation aspect
- Comparing sorted arrays after checking two conditions:
  - All elements of 'a' equal to 'b' (k=0 case)
  - All elements of 'a' are exactly 1 less than 'b' (k=n case)

Time Complexity: O(n log n) due to sorting, where n is the size of the arrays.
Space Complexity: O(1) as we use a constant amount of extra space (arrays are of fixed size).
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int T;
  for (cin >> T; T--;) {
    int n, a[109], b[109], Ans = 1;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i];
    sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; i++)
      if (a[i] != b[i] && a[i] != b[i] - 1) // Check if a[i] equals b[i] or a[i] is 1 less than b[i]
        Ans = 0;
    puts(Ans ? "Yes" : "No");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/