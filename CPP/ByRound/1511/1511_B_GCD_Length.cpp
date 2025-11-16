// Problem: CF 1511 B - GCD Length
// https://codeforces.com/contest/1511/problem/B

/*
Purpose: This code solves the problem of finding two positive integers x and y such that:
         - x has exactly 'a' digits
         - y has exactly 'b' digits
         - gcd(x, y) has exactly 'c' digits
Algorithm:
         - First, construct a number g with exactly 'c' digits by repeatedly multiplying by 2 until it has 'c' digits.
         - Then, construct x as g multiplied by powers of 3 until x has exactly 'a' digits.
         - Similarly, construct y as g multiplied by powers of 5 until y has exactly 'b' digits.
Time Complexity: O(a + b + c) per test case, since we're doing simple loops and digit counting.
Space Complexity: O(1), only using a few variables for computation.
*/
#include <cstdio>
typedef long long ll;

// Function to count the number of digits in a number
ll digits(ll z) {
  ll cnt(0);
  while (z > 0) {
    z /= 10;
    ++cnt;
  }
  return cnt;
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    
    // Start with g = 1 and keep doubling until it has exactly 'c' digits
    ll g(1);
    while (digits(g) < c) {
      g *= 2;
    }
    
    // Construct x starting from g, multiplying by 3 until it has exactly 'a' digits
    ll x(g);
    while (digits(x) < a) {
      x *= 3;
    }
    
    // Construct y starting from g, multiplying by 5 until it has exactly 'b' digits
    ll y(g);
    while (digits(y) < b) {
      y *= 5;
    }
    
    printf("%lld %lld\n", x, y);
  }
}


// https://github.com/VaHiX/CodeForces/