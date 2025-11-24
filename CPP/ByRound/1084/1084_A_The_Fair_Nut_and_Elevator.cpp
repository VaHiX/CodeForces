// Problem: CF 1084 A - The Fair Nut and Elevator
// https://codeforces.com/contest/1084/problem/A

/*
 * Problem: A. The Fair Nut and Elevator
 * Purpose: Find the optimal floor x for the elevator to minimize total electricity usage
 *          for all residents in a building with n floors.
 *
 * Algorithm:
 *   - For each possible floor x (0 to n-1) as the elevator's resting position:
 *     - Calculate total electricity cost for all people moving to/from their floors
 *     - Each person on floor i uses elevator twice daily:
 *       - To go from floor i to floor 0: moves |i - x| + i + x units (x -> i -> 0)
 *       - To go from floor 0 to floor i: moves |0 - x| + 0 + x units (0 -> x -> i)
 *     - Cost = sum(2 * a[i] * (|i - x| + i + x))
 *   - Return minimum cost over all possible x values
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
long mabs(long x) { return (x > 0) ? x : -x; }
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read number of people on each floor
  }
  long mn(1e9); // Initialize minimum cost to large value
  for (long x = 0; x < n; x++) { // Try each floor as the elevator resting position
    long sum(0);
    for (long p = 0; p < n; p++) {
      // Compute total electricity cost for person on floor p using elevator resting at x
      sum += 2 * a[p] * (mabs(p - x) + p + mabs(x)); // Simplified calculation of travel distance
    }
    mn = (mn < sum) ? mn : sum; // Update minimum cost
  }
  printf("%ld\n", mn); // Output the minimum electricity cost
  return 0;
}


// https://github.com/VaHiX/codeForces/