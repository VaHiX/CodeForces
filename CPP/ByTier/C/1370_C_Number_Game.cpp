// Problem: CF 1370 C - Number Game
// https://codeforces.com/contest/1370/problem/C

/*
C. Number Game
Purpose: Determine the winner of a game where two players (Ashishgup and FastestFinger) take turns modifying a number n.
Players can either:
1. Divide n by any odd divisor > 1
2. Subtract 1 from n if n > 1
The player unable to make a move loses.
Algorithm: 
- For each n, analyze its prime factorization.
- The key insight is based on winning/losing positions in combinatorial game theory.
- If n == 1, Ashishgup loses immediately (no moves).
- If n is even:
    - Count how many times it can be divided by 2 (let's call this m).
    - If m > 1 then it's a winning position for Ashishgup (can subtract 1 to force a move).
    - If m = 1, check if n/2 has any odd divisors > 1.
        - If yes, then it's also a winning position.
        - If no, then it's losing.
- If n is odd:
    - If n > 1, it must be prime or composite.
    - If it's prime and not equal to 2, Ashishgup can only divide by itself.
    - If it's even (but in the loop we already removed powers of 2), it has no odd divisors except 1.
Time Complexity: O(sqrt(n)) per test case due to factorization check
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long m(0); // Count of factors of 2
    while (n % 2 == 0) { // Remove all powers of 2
      n /= 2;
      ++m;
    }
    bool q(false); // Whether n has an odd divisor greater than 1
    for (long p = 2; p * p <= n; p++) { // Check for smallest odd divisor
      if (n % p == 0) {
        q = true;
        break;
      }
    }
    puts(((n == 1 && m != 1) || (n != 1 && m == 1 && !q)) ? "FastestFinger"
                                                          : "Ashishgup");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/