// Problem: CF 2127 B - Hamiiid, Haaamid... Hamid?
// https://codeforces.com/contest/2127/problem/B

/*
B. Hamiiid, Haaamid... Hamid?
Problem: Determine the minimum number of days Hamid needs to escape a 1×n grid,
         given optimal play by both Hamid and Mani.

Algorithms/Techniques:
- Two-pointer technique to find nearest walls on both sides of Hamid's position
- Greedy strategy for both players:
    - Mani tries to maximize the escape time.
    - Hamid tries to minimize it.

Time Complexity: O(n) per test case (linear scan)
Space Complexity: O(n) for storing the string input

*/
#include <algorithm>
#include <cstdio>
using namespace std;
char a[200010];  // Array to store the grid state
int main() {
  int T;
  scanf("%d", &T);  // Read number of test cases
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);  // Read grid size and Hamid's initial position
    scanf("%s", a + 1);    // Read the string representation of the grid (1-indexed)

    int l = k, r = k, ans = 0x3f3f3f3f;  // l: left wall pointer, r: right wall pointer

    // Move left pointer to find the nearest wall to the left of k
    while (a[l] == '.')
      l--;
    
    // Move right pointer to find the nearest wall to the right of k
    while (a[r] == '.')
      r++;

    // Calculate minimum days required for Hamid to escape:
    // - Either escape from the left side: min(k-1, n-r+1) 
    // - Or escape from the right side: min(n-(k+1)+1, l)
    // Add 1 since day count starts at 1
    printf("%d\n", max(min(k - 1, n - r + 1), min(n - (k + 1) + 1, l)) + 1);
  }
}


// https://github.com/VaHiX/codeForces/