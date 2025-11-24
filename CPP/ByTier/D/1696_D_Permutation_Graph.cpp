// Problem: CF 1696 D - Permutation Graph
// https://codeforces.com/contest/1696/problem/D

/*
Purpose: This code solves the problem of finding the shortest path from vertex 1 to vertex n in a permutation graph, 
where edges are added based on min/max conditions over subarrays.
The algorithm works by scanning the array from left to right and then from right to left to count how many 
edges would be formed, then adjusts for double counting and returns the result.

Algorithms/Techniques:
- Linear scan with tracking of minimum and maximum values.
- Reversal of array to simulate two-directional traversal.
- Edge counting technique to determine shortest path length.

Time Complexity: O(n) per test case, where n is the size of the permutation.
Space Complexity: O(n) for storing the permutation array.

*/
#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;
const int N = 25e4 + 1;
int n, ans, a[N];

// Function to count edges in one direction (left to right)
void ooo() {
  int mn = a[1], mx = a[1], flag = 2;  // flag tracks which endpoint is larger (0 for left, 1 for right)
  for (int i = 2; i <= n; i++) {
    if (a[i] < mn) {
      mn = a[i];
      flag ^ 0 ? ans++, flag = 0 : 0;  // Increment if previous endpoint was right
    }
    if (a[i] > mx) {
      mx = a[i];
      flag ^ 1 ? ans++, flag = 1 : 0;  // Increment if previous endpoint was left
    }
  }
}

// Function to process each test case
void xxx() {
  scanf("%d", &n);
  ans = 0;
  for (int i = 1; i <= n; i++)
    scanf("%d", a + i);
  ooo();  // First pass: left to right
  reverse(a + 1, a + 1 + n);  // Reverse array to simulate reverse pass
  ooo();  // Second pass: right to left
  printf("%d\n", max(ans - 1, 0));  // Adjust for double counting and ensure non-negative result
}

int main() {
  int T;
  for (scanf("%d", &T); T--;)
    xxx();
  return 0;
}


// https://github.com/VaHiX/CodeForces/