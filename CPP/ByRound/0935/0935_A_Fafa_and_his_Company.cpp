// Problem: CF 935 A - Fafa and his Company
// https://codeforces.com/contest/935/problem/A

/*
Purpose: This program calculates the number of ways to choose the number of team leaders 'l' 
         such that n employees can be evenly distributed among them, with each team leader 
         managing the same number of employees.

Algorithm: 
- We iterate through all possible divisors of n from 2 to sqrt(n).
- For each divisor p of n:
  - If p is a divisor, then n/p is also a divisor.
  - We count both p and n/p as valid numbers of team leaders (unless p = sqrt(n), in which case we count it only once).
- The answer is the total count of such valid divisors plus 1 (for the case where all employees are team leaders themselves).

Time Complexity: O(sqrt(n)) - We loop up to sqrt(n) to find divisors.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long cnt(1);  // Start with 1 because n itself is always a valid choice (all employees are team leaders)
  for (long p = 2; p * p <= n; p++) {  // Check divisors from 2 up to sqrt(n)
    if (n % p) {  // If p is not a divisor of n, skip it
      continue;
    }
    cnt += 2 - (p * p == n);  // Add 2 if both p and n/p are distinct divisors, otherwise add 1
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/