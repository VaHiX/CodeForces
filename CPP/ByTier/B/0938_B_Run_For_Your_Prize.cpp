// Problem: CF 938 B - Run For Your Prize
// https://codeforces.com/contest/938/problem/B

/*
Algorithm: Dynamic Programming with Optimization
Approach:
- We model this as a problem where we need to divide the prizes between two people (you and your friend).
- You start at position 1, and your friend starts at position 10^6.
- The key insight is that we can iterate through all possible ways to split the prizes:
  - One person takes prizes from the beginning, and the other takes the rest.
  - For each such split, compute the maximum time needed by either person.
- The optimal solution is the minimum of all such maximum times.

Time Complexity: O(n) - Single pass over the array.
Space Complexity: O(n) - To store the positions in a vector.

The solution uses the idea of considering all valid splits and then finding the split that minimizes the maximum time required for the two participants.
*/
#include <cstdio>
#include <vector>
long mymax(long x, long y) { return (x > y) ? x : y; }
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n + 2);  // Create vector with extra space for start and end
  for (long p = 1; p <= n; p++) {
    scanf("%ld", &a[p]);
  }
  a[0] = 1;           // Your initial position
  a[n + 1] = 1e6;     // Friend's initial position
  long mn(1e7);       // Initialize minimum time to a large value
  for (long p = 0; p <= n; p++) {
    // For each split point p:
    // - Person 1 (you) takes prizes from 0 to p
    // - Person 2 (friend) takes prizes from p+1 to n+1
    // Compute the max time taken by either participant, and update global minimum
    long cand = mymax((a[p] - 1), (1e6 - a[p + 1]));
    mn = (mn < cand) ? mn : cand;  // Update minimum time
  }
  printf("%ld\n", mn);
  return 0;
}


// https://github.com/VaHiX/CodeForces/