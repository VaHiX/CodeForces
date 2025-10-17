// Problem: CF 1860 B - Fancy Coins
// https://codeforces.com/contest/1860/problem/B

/*
B. Fancy Coins

Algorithm:
This problem involves minimizing the number of "fancy" coins used in making a purchase of exactly m burles, 
using two types of coins (1 burle and k burles) with limited quantities of regular coins.

Approach:
- The idea is to use as many regular coins as possible to minimize fancy coin usage.
- For each test case:
  - Calculate how many k-burle regular coins we can use: x = m / k
  - Determine how many 1-burle regular coins are needed: rs = m % k
  - If we don't have enough 1-burle regular coins, calculate shortfall
  - If we still need more coins, we might need to use fancy coins for either type.
- The solution tries all valid combinations of regular coin usage and finds the minimum fancy coin usage.

Time Complexity: O(1) per test case — Constant time computation involving basic arithmetic operations.
Space Complexity: O(1) — Only using a fixed amount of variables regardless of input size.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long m, k, a, b;
    scanf("%ld %ld %ld %ld", &m, &k, &a, &b);
    long x = m / k; // Number of k-burle coins needed if we use as many as possible
    long rs = m % k; // Remaining burles after using max k-coins
    long fs = rs - a; // Extra 1-burle coins needed (shortfall from regular supply)
    fs = (fs > 0) ? fs : 0; // If positive, we need that many fancy 1-burle coins
    long ls = a - rs; // Surplus of 1-burle coins after allocating rs to meet m%k
    ls = (ls > 0) ? ls : 0; // If there are extra, these can help reduce fancy usage
    long fk = x - b; // Extra k-burle coins needed if we use max regular k-coins
    fk = (fk > 0) ? fk : 0; // If positive, we need this many fancy k-coins
    long cnt = fs + fk - (ls / k < fk ? (ls / k) : fk); // Adjusted fancy coins used
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/