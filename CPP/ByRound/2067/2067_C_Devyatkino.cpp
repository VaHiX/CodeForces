// Problem: CF 2067 C - Devyatkino
// https://codeforces.com/contest/2067/problem/C

/*
C. Devyatkino
Algorithm: For each test case, we try all possible numbers of operations from 0 to 9.
For a given number of operations k (from 0 to 9), we check if there exists a way 
to make the number n contain digit 7 by adding k numbers, each consisting only of 9s.
We do this by considering how many 9s we add at each digit position to make a digit 7,
and ensure it's feasible.

Time Complexity: O(1) per test case, since we iterate at most 10 times (for k from 0 to 9),
and for each k, we process the digits of n which is bounded by log10(n) <= 9.
Space Complexity: O(1), only using constant extra space.

*/
#include <stdio.h>
#include <algorithm>

using namespace std;
int _;
int main() {
  scanf("%d", &_);
  for (; _--;) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= 9; i++) {  // Try up to 9 operations
      int k = n - i, mi = 7;        // k is the value of n after subtracting i
      for (; k > 0; mi = min(mi, (17 - k % 10) % 10), k /= 10)  // Check each digit
        ;                                           // mi stores minimal cost for this k
      if (mi <= i) {                                // If minimum cost is within allowed operations
        printf("%d\n", i);                          // Output the number of operations
        break;
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/