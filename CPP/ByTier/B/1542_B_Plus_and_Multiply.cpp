// Problem: CF 1542 B - Plus and Multiply
// https://codeforces.com/contest/1542/problem/B

/*
B. Plus and Multiply
Problem Description:
Given a set starting with 1, and rules that if x is in the set then both x*a and x+b are also in the set,
determine whether a given number n can be generated from this set.

Algorithms/Techniques:
- Tree traversal simulation with BFS-like approach
- Optimization for special cases (a=1 or b=1)
- Iterative generation of powers of 'a' up to n

Time Complexity: O(log_a(n) * log_b(n)) in worst case, but typically much faster due to early termination.
Space Complexity: O(1) - only using a few variables for computation.

*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll a, b, n;
    scanf("%lld %lld %lld", &n, &a, &b);
    
    // Special case: if b is 1, every number can be formed by adding 1 multiple times
    if (b == 1) {
      puts("Yes");
      continue;
    } 
    // Special case: if a is 1, then only numbers of form 1 + k*b are possible
    else if (a == 1) {
      puts(n % b == 1 ? "Yes" : "No");
      continue;
    }
    
    ll u(1);           // Start with 1 (the base number)
    bool ans(false);   // Flag to store whether n is achievable
    
    // Generate all possible powers of a that are <= n
    while (u <= n) {
      // Check if (n - u) is divisible by b => (n % b == u % b)
      if (n % b == u % b) {
        ans = true;
        break;
      }
      // If current power of a exceeds n, stop
      if (u > n / a) break;
      u *= a;   // Move to next power of a
    }
    
    puts(ans ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/