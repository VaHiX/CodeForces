// Problem: CF 767 A - Snacktower
// https://codeforces.com/contest/767/problem/A

/*
Code Purpose:
This program simulates the construction of a Snacktower based on the order in which snacks fall.
Snacks must be stacked such that the largest snack is at the bottom and the smallest at the top.
When a snack falls, it is placed on the tower immediately if all larger snacks have already fallen.
Otherwise, it waits until the required larger snacks have fallen.

Algorithms/Techniques:
- Use a boolean vector to track which snack sizes have fallen.
- Keep a pointer 'next' to the largest snack that can currently be placed on the tower.
- For each incoming snack, mark it as fallen and try to place all subsequent snacks that are ready.

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<bool> a(n + 1);  // Boolean vector to track which snack sizes have fallen
  long next = n;               // Pointer to the largest snack that can currently be placed
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    a[x] = 1;                  // Mark the snack of size x as fallen
    while (a[next] == 1) {     // While the snack of size 'next' has fallen
      printf("%ld ", next);    // Place it on the tower
      --next;                  // Move to the next smaller snack
    }
    puts("");                  // Print a newline after placing all possible snacks
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/