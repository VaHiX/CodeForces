// Problem: CF 490 D - Chocolate
// https://codeforces.com/contest/490/problem/D

/*
 * Problem: Chocolate
 * Purpose: Determine the minimum number of steps to make two chocolate bars have the same number of squares,
 *          where each step involves cutting a bar into halves or thirds and eating one piece.
 * 
 * Algorithms/Techniques: 
 * - Mathematical approach using GCD and prime factorization
 * - Greedy strategy to balance the powers of 2 and 3 in the factorization
 * 
 * Time Complexity: O(log(min(a1*b1, a2*b2))) due to GCD computation and factorization steps
 * Space Complexity: O(1) - only using a constant amount of extra space
 */

#include <cstdio>
typedef long long ll;

// Function to compute greatest common divisor using Euclidean algorithm
ll gcd(ll a, ll b) { 
    return (b == 0) ? a : gcd(b, a % b); 
}

int main() {
  ll a1, b1, a2, b2;
  scanf("%lld %lld %lld %lld", &a1, &b1, &a2, &b2);
  
  // Calculate total areas of both bars
  ll x1 = a1 * b1;
  ll x2 = a2 * b2;
  
  // Remove all factors of 2 and 3 from x1
  while (x1 % 2 == 0) {
    x1 /= 2;
  };
  while (x1 % 3 == 0) {
    x1 /= 3;
  }
  
  // Remove all factors of 2 and 3 from x2
  while (x2 % 2 == 0) {
    x2 /= 2;
  };
  while (x2 % 3 == 0) {
    x2 /= 3;
  }
  
  // If x1 != x2, then it's impossible to make both bars equal
  if (x1 != x2) {
    puts("-1");
  } else {
    // Reset x1 and x2 to their original values
    ll t1(0), h1(0), t2(0), h2(0);
    x1 = a1 * b1;
    x2 = a2 * b2;
    
    // Find GCD of both areas
    ll g = gcd(x1, x2);
    x1 /= g;
    x2 /= g;
    
    // Count how many powers of 2 and 3 are in x1
    while (x1 % 2 == 0) {
      ++t1;
      x1 /= 2;
    }
    while (x1 % 3 == 0) {
      ++h1;
      x1 /= 3;
    }
    
    // Count how many powers of 2 and 3 are in x2
    while (x2 % 2 == 0) {
      ++t2;
      x2 /= 2;
    }
    while (x2 % 3 == 0) {
      ++h2;
      x2 /= 3;
    }
    
    ll steps(0);
    
    // Reduce excess 3's by converting them into 2's
    while (h1 > 0) {
      --h1;
      ++t1;
      ++steps;
      if (a1 % 3 == 0) {
        a1 /= 3;
        a1 *= 2;
      } else if (b1 % 3 == 0) {
        b1 /= 3;
        b1 *= 2;
      }
    }
    
    // Reduce excess 3's by converting them into 2's for second bar
    while (h2 > 0) {
      --h2;
      ++t2;
      ++steps;
      if (a2 % 3 == 0) {
        a2 /= 3;
        a2 *= 2;
      } else if (b2 % 3 == 0) {
        b2 /= 3;
        b2 *= 2;
      }
    }
    
    // Even out 2's in both bars
    while (t1 != t2) {
      ++steps;
      if (t1 > t2) {
        --t1;
        if (a1 % 2 == 0) {
          a1 /= 2;
        } else {
          b1 /= 2;
        }
      } else {
        --t2;
        if (a2 % 2 == 0) {
          a2 /= 2;
        } else {
          b2 /= 2;
        }
      }
    }
    
    // Output result
    printf("%lld\n", steps);
    printf("%lld %lld\n%lld %lld\n", a1, b1, a2, b2);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/