// Problem: CF 1545 A - AquaMoon and Strange Sort
// https://codeforces.com/contest/1545/problem/A

/*
A. AquaMoon and Strange Sort
Algorithms/Techniques: Sorting, Greedy, Array Manipulation

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

The problem involves sorting an array using adjacent swaps with direction flips,
with the constraint that all friends must face right at the end.
The approach separates elements into two groups based on their positions (even/odd indices),
sorts each group independently, and checks if placing elements in order maintains non-decreasing property
while ensuring final directions are right.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 1e5 + 7;
int T_T, n, i, j, a[2][N]; // a[0] stores even-indexed elements, a[1] stores odd-indexed elements

int main() {
  for (scanf("%d", &T_T); T_T--;) {
    for (scanf("%d", &n), i = 1; i <= n; ++i)
      scanf("%d", a[i & 1] + (i + 1) / 2); // Store elements in even/odd indexed arrays
    sort(a[0] + 1, a[0] + n / 2 + 1); // Sort the even-indexed group
    sort(a[1] + 1, a[1] + (n + 1) / 2 + 1); // Sort the odd-indexed group
    for (j = 0, i = 1; i <= n; ++i)
      if (a[i & 1][(i + 1) / 2] < a[(i - 1) & 1][i / 2]) { // Check if current element is less than previous one when properly ordered
        puts("NO");
        j = 1;
        break;
      }
    if (!j)
      puts("YES");
  }
}


// https://github.com/VaHiX/codeForces/