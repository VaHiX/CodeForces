// Problem: CF 2031 C - Penchick and BBQ Buns
// https://codeforces.com/contest/2031/problem/C

/*
Algorithm/Techniques: 
- The solution uses a pattern-based approach to assign fillings to BBQ buns.
- For odd n, it checks if n is small (<=25), and if so, returns -1 as it's impossible to satisfy the constraints.
- For larger odd n, it assigns a fixed sequence of fillings to the first 27 buns, then continues with the pattern.
- For even n, it directly assigns fillings in pairs to ensure distances are perfect squares.
- Time Complexity: O(n) per test case, as we process each bun once.
- Space Complexity: O(1), no extra space used apart from variables.

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
int T, n;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int x(1); // Starting filling number
    if (n & 1) { // If n is odd
      if (n <= 25) { // If n is too small to allow a valid assignment
        puts("-1");
        continue;
      }
      // Assign a fixed sequence for the first 27 buns to satisfy the condition
      printf("1 2 2 3 3 4 4 5 5 1 6 6 7 7 8 8 9 9 10 10 11 11 13 12 12 1 13 "),
          x = 14, n -= 27; // Update x and reduce n
    }
    n >>= 1; // Divide n by 2 to account for pairs
    for (int i(0); i < n; ++i)
      printf("%d %d ", x + i, x + i); // Assign pairs of same fillings
    puts(""); // Print new line at the end of each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/