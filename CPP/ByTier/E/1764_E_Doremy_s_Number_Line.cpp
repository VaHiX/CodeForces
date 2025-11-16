// Problem: CF 1764 E - Doremy's Number Line
// https://codeforces.com/contest/1764/problem/E

/*
Algorithm: Greedy with Sorting
Time Complexity: O(n * log(n)) due to sorting
Space Complexity: O(n) for storing the array of nodes

Approach:
1. We sort the array from index 2 to n based on A values.
2. We simulate the process of coloring the number line.
3. For the first element (index 1), we check if k can be colored with color 1.
   - If k is less than or equal to A[1], it's possible.
   - Otherwise, we compute how far we can reach from the first element
     by simulating the coloring process with sorted elements starting from index 2.
4. The logic involves maintaining a pointer 'p' that tracks the maximum reachable point
   from the start, and using greedy decisions to determine reachability.

Key observations:
- The first color (color 1) is special because we try to reach k with it.
- Sorting allows us to process the elements in an order that enables efficient greedy selection.
- The condition check at the end determines whether point k can be colored with color 1.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int maxn = 300010;
int T, n, k;
struct Node {
  int A, B;
} L[maxn];
bool cmp(Node u, Node v) { return u.A < v.A; }
int main() {
  cin >> T;
  for (int C = 1; C <= T; C++) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
      cin >> L[i].A >> L[i].B;
    sort(L + 2, L + n + 1, cmp); // Sort elements from index 2 to n based on A value
    int p = -1e9; // Track the farthest point reachable so far (greedy approach)
    for (int i = 2; i <= n; i++) {
      if (p <= L[i].A)
        p = max(L[i].A, p + L[i].B); // If we can start from this point to cover more
      else
        p = max(p, L[i].A + L[i].B); // Else update using current element
      if (i > 2)
        p = max(p, L[i - 1].A + L[i - 1].B); // Ensure the previous value is also considered
    }
    if (k <= L[1].A)
      puts("YES"); // Trivial case: k is within reach of first node
    else if (p >= L[1].A && k <= L[1].A + L[1].B)
      puts("YES"); // If k is within the reach of the first node
    else if (p <= L[1].A && k <= p + L[1].B)
      puts("YES"); // If k can be reached using a path with the first node
    else
      puts("NO"); // Otherwise, impossible
  }
}


// https://github.com/VaHiX/CodeForces/