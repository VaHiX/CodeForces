// Problem: CF 1238 A - Prime Subtraction
// https://codeforces.com/contest/1238/problem/A

/*
Problem: Prime Subtraction
Algorithm: Check if x - y is greater than 1
Technique: Mathematical property of primes
Time Complexity: O(1) per test case
Space Complexity: O(1)

Given two integers x and y (x > y), determine if we can make x equal to y by subtracting any prime number p from x any number of times.
Key observation: If x - y > 1, then we can always find a prime number p such that x - k*p = y for some integer k.
This is because:
- If x - y is even and greater than 2, we can use p = 2
- If x - y is odd and greater than 1, we can use p = 3 (since any odd number > 1 can be expressed as difference of primes)
- The only exception is when x - y = 1, which means no prime subtraction can achieve this.

Sample Input:
4
100 98
42 32
1000000000000000000 1
41 40

Sample Output:
YES
YES
YES
NO
*/

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll x, y;
    scanf("%lld %lld", &x, &y);
    puts(x - y > 1 ? "YES" : "NO"); // If difference is greater than 1, answer is YES; otherwise NO
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/