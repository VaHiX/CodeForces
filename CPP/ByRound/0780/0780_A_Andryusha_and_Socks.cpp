// Problem: CF 780 A - Andryusha and Socks
// https://codeforces.com/contest/780/problem/A

/*
Code Purpose:
This program determines the maximum number of socks that were on the table at the same time during Andryusha's process of putting socks into the wardrobe. 
It simulates the process of taking socks from a bag and placing them on the table or putting pairs into the wardrobe.

Algorithm:
- Use a boolean array to track whether a sock pair is on the table.
- For each sock taken:
  - If its pair is already on the table, remove the pair from the table (decrease count).
  - Otherwise, place the sock on the table (increase count).
- Keep track of the maximum count of socks on the table at any time.

Time Complexity: O(n), where n is the number of pairs. Each sock is processed exactly once.
Space Complexity: O(n), for the array storing the state of each sock pair.
*/

#include <cstdio>
int n, t, a[200000], c, m;
int main() {
  scanf("%d", &n);
  n <<= 1;  // n = 2 * n, since there are 2*n socks total
  while (n--) {
    scanf("%d", &t);
    c += a[t] ? -1 : 1;  // If pair is already on table (a[t] == 1), decrease count; else increase
    m = m > c ? m : c;   // Update maximum number of socks on table
    a[t] ^= 1;           // Toggle the state of the sock pair (0 -> 1 or 1 -> 0)
  }
  printf("%d", m);
}


// https://github.com/VaHiX/CodeForces/