// Problem: CF 1176 A - Divide it!
// https://codeforces.com/contest/1176/problem/A

/*
 * Problem: Minimum Operations to Reduce Number to 1
 * 
 * Algorithms/Techniques: Greedy approach with division operations
 * 
 * Time Complexity: O(log n) per query, since we divide the number by factors (2,3,5)
 * Space Complexity: O(1), only using a constant amount of extra space
 * 
 * Description:
 * Given an integer n, we can perform three operations:
 * 1. Divide by 2 if divisible by 2 (costs 1 step)
 * 2. Divide by 3 if divisible by 3 (costs 2 steps)
 * 3. Divide by 5 if divisible by 5 (costs 3 steps)
 * 
 * Goal: Find the minimum number of operations to reduce n to 1.
 * If it's impossible, return -1.
 * 
 * Strategy:
 * Greedily apply the operation that divides by the largest factor (2,3,5) available.
 * If none of these are divisible, return -1.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll q;
  scanf("%lld", &q); // Read number of queries
  while (q--) {
    ll n;
    scanf("%lld", &n); // Read current number
    ll cnt(0); // Initialize operation count
    
    // Continue until n becomes 1
    while (n > 1) {
      if (n % 2 == 0) { // If divisible by 2
        n /= 2;       // Perform division
        ++cnt;        // Increment step count
      } else if (n % 3 == 0) { // If divisible by 3
        n /= 3;       // Perform division
        cnt += 2;     // Increment step count by 2
      } else if (n % 5 == 0) { // If divisible by 5
        n /= 5;       // Perform division
        cnt += 3;     // Increment step count by 3
      } else {
        cnt = -1;     // Impossible to reduce further, mark as invalid
        break;
      }
    }
    printf("%lld\n", cnt); // Print result for this query
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/