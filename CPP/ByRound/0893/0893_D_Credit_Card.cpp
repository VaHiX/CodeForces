// Problem: CF 893 D - Credit Card
// https://codeforces.com/contest/893/problem/D

/*
Code Purpose:
This program determines the minimum number of days Luba needs to deposit money 
into her credit card account such that:
1. The account balance never exceeds a given limit 'd'.
2. Every time the balance is checked (when a_i == 0), it is non-negative.
3. If it's impossible to meet these conditions, return -1.

Algorithms/Techniques:
- Simulation with tracking of minimum and maximum possible balance at each step.
- Greedy approach to minimize the number of deposits needed.

Time Complexity: O(n), where n is the number of days.
Space Complexity: O(1), only using a constant amount of extra space.

*/
#include <cstdio>
int main() {
  long n, d;
  scanf("%ld %ld", &n, &d);
  long mn(0), mx(0), count(0);
  bool possible(true);
  while (n--) {
    long x;
    scanf("%ld", &x);
    if (x == 0) {
      // If balance at check day is non-negative, no deposit needed
      if (mx >= 0) {
        mn = (mn > 0) ? mn : 0;  // Reset mn to non-negative if needed
      } else {
        // Need to deposit money to make balance non-negative
        ++count;
        mn = 0;
        mx = d;  // Reset mx to maximum allowed after deposit
      }
    } else {
      // Process transaction (deposit or withdrawal)
      mn += x;
      mx += x;
      // If balance exceeds limit, configuration is impossible
      if (mn > d) {
        possible = false;
        break;
      }
      // Ensure balance does not exceed 'd'
      mx = (mx < d) ? mx : d;
    }
  }
  printf("%ld\n", possible ? count : -1);
  return 0;
}


// https://github.com/VaHiX/CodeForces/