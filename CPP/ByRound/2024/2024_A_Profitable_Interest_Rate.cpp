// Problem: CF 2024 A - Profitable Interest Rate
// https://codeforces.com/contest/2024/problem/A

/*
Problem: Maximize coins in "Profitable" deposit
Algorithms/Techniques: Greedy approach
Time Complexity: O(1) per test case
Space Complexity: O(1)

Alice has 'a' coins and needs 'b' coins to open the "Profitable" deposit.
She can first deposit some coins into the "Unprofitable" deposit,
which reduces the required amount for "Profitable" by 2x (where x is the coins deposited).
Goal: Find maximum coins that can be deposited in "Profitable" deposit.

Key logic:
- If a >= b, simply use all 'a' coins for profitable deposit
- Else if 2*a >= b, we can reduce the requirement to (b - 2*a) and use 2*a - b coins
- Otherwise, we cannot open profitable deposit
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long res(0);
    if (a >= b) {              // If we can open profitable deposit with all coins
      res = a;
    } else if (2 * a >= b) {   // If we can reduce requirement enough to open profitable deposit
      res = 2 * a - b;         // Remaining coins after reducing required amount
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/