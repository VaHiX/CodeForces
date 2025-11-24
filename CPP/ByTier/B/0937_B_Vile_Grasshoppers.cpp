// Problem: CF 937 B - Vile Grasshoppers
// https://codeforces.com/contest/937/problem/B

/*
 * Code Purpose:
 *   Find the highest branch number from 'p+1' to 'y' that is not reachable by any grasshopper,
 *   where grasshoppers on branch 'x' can jump to branches x, 2*x, 3*x, ... as long as they are <= y.
 *   A branch is suitable if it's not reachable by any grasshopper.
 *
 * Algorithm:
 *   - For each branch from y down to p+1, check if it's a prime number <= p.
 *   - If it's a prime number, it cannot be reached by any grasshopper (since it's not divisible by any number from 2 to p).
 *   - Return the first such prime number found (highest one due to reverse iteration).
 *   - If no such prime exists, return -1.
 *
 * Time Complexity: O((y-p) * sqrt(p))  
 *   - Loop runs (y - p) times, and for each checkPrime takes O(sqrt(p)) time.
 * Space Complexity: O(1)
 *   - Only using a constant amount of extra space.
 */

#include <cstdio>

// Function to check if a number x is prime up to a given limit a
bool checkPrime(long x, long a) {
  for (long p = 2; p <= a && p * p <= x; p++) { // Iterate up to min(a, sqrt(x))
    if (x % p == 0) { // If x is divisible by p, then it's not prime
      return false;
    }
  }
  return true; // x is prime
}

int main() {
  long a, y;
  scanf("%ld %ld", &a, &y);
  long res(-1); // Initialize result to -1, indicating no valid branch found yet
  for (long p = y; p > a; p--) { // Start from y and go down to a+1
    if (checkPrime(p, a)) { // If p is a prime number <= a, it's not reachable
      res = p; // Store the highest suitable branch
      break; // Since we iterate from top to bottom, first match is the answer
    }
  }
  printf("%ld\n", res); // Print the result
  return 0;
}


// https://github.com/VaHiX/CodeForces/