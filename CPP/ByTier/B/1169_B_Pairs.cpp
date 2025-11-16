// Problem: CF 1169 B - Pairs
// https://codeforces.com/contest/1169/problem/B

/*
B. Pairs
Algorithm: DFS-based brute force approach to check if there exist two integers x and y such that every pair contains at least one of them.

Time Complexity: O(m * n) in worst case due to recursive calls, but often much better in practice.
Space Complexity: O(n + m) for storing the pairs and recursion stack space.

Approaches:
- For each possible pair of values (x,y), check if all pairs contain at least one of them.
- A recursive DFS-based method is used where we traverse the graph formed by pairs to see if a valid x,y exists.
*/

#include <cstdio>
#include <iosfwd>

using namespace std;
int n, m, a[300005], b[300005];

// Function to check if there exists such x and y starting from given x and y
bool f(int x, int y) {
  for (int i = 1; i <= m; i++) {
    // If current pair contains x or y, skip it
    if (a[i] == x || a[i] == y || b[i] == x || b[i] == y)
      continue;
    // If we have no valid y yet and we can't handle this pair with current x
    if (y)
      return 0;
    // Try to find a recursive solution by assigning the other element of the pair to y
    return f(a[i], x) || f(b[i], x);
  }
  return 1;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++)
    scanf("%d%d", &a[i], &b[i]);
  
  // Try two initial cases: start with first pair's elements
  if (f(a[1], 0) || f(b[1], 0))
    printf("YES");
  else
    printf("NO");
  return 0;
}


// https://github.com/VaHiX/codeForces/