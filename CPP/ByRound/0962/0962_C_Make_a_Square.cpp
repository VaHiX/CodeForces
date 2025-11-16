// Problem: CF 962 C - Make a Square
// https://codeforces.com/contest/962/problem/C

/*
Algorithm: Generate all perfect squares up to n and check if the digits of n can be rearranged to form the square.
           For each perfect square, check if it's a subsequence of the given number n.
           If yes, count how many digits have to be deleted from n to form that square.
           Keep track of minimum deletions required.

Time Complexity: O(sqrt(n) * log(n)) - We loop up to sqrt(n) and for each square, we do digit comparison.
Space Complexity: O(1) - Only a few variables are used.

Techniques:
- Brute force generation of perfect squares
- Digit matching to determine subsequence
- Tracking minimum operations needed
*/

#include <cstdio>

typedef long long ll;
int check(ll s, ll t) {
  int cnt(0);
  while (s > 0) {
    if (t == 0 || ((s % 10) != (t % 10))) {
      // If t is exhausted or last digit doesn't match, we need to delete this digit
      ++cnt;
    } else {
      // If the last digits match, move to next digit in t
      t /= 10;
    }
    s /= 10;  // Move to next digit in s
  }
  if (t > 0) {
    // If t still has digits left, then s is not a subsequence of t
    return -1;
  }
  return cnt;  // Return number of deletions required
}
int main() {
  ll n;
  scanf("%lld", &n);
  ll x(0);
  int minCnt(-1);
  while (x * x <= n) {
    ++x;
    int tmp = check(n, x * x);
    if (tmp < 0) {
      continue;  // Skip if not a valid subsequence
    }
    if (minCnt < 0 || tmp < minCnt) {
      minCnt = tmp;  // Update minimum deletions
    }
  }
  printf("%d\n", minCnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/