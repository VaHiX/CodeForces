// Problem: CF 1061 A - Coins
// https://codeforces.com/contest/1061/problem/A

/*
Problem: Minimum Coins to Reach Sum S
Algorithm: Greedy approach
Time Complexity: O(1)
Space Complexity: O(1)

Given coins with values 1, 2, ..., n, find the minimum number of coins needed to sum up to S.
The optimal strategy is to use as many coins of value n as possible, then handle the remainder.
Since we can use unlimited coins, the minimum number of coins is (S + n - 1) / n.
This works because:
- If S is divisible by n, we need exactly S/n coins
- Otherwise, we need S/n + 1 coins, which equals (S + n - 1) / n due to integer division behavior
*/

#include <cstdio>
int main() {
  long n, s;
  scanf("%ld %ld", &n, &s);
  long cnt = (s + n - 1) / n;  // Calculate minimum coins needed using ceiling division
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/