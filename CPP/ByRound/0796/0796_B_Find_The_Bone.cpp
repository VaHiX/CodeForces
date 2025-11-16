// Problem: CF 796 B - Find The Bone
// https://codeforces.com/contest/796/problem/B

/*
 * Problem: Find The Bone
 * 
 * Purpose: Simulate a series of cup swaps to track where a bone ends up,
 *          taking into account that the bone falls into a hole if it is 
 *          present at the position of a hole during any swap operation.
 * 
 * Algorithms/Techniques:
 * - Simulation of swaps with early termination when bone falls into a hole
 * - Efficient lookup of hole positions using a boolean vector
 * 
 * Time Complexity: O(n + k)
 *   - O(n) for initializing the hole vector
 *   - O(k) for processing the swaps
 * 
 * Space Complexity: O(n)
 *   - Space for the hole vector of size n+1
 */
#include <cstdio>
#include <vector>
int main() {
  long n, m, k;
  scanf("%ld %ld %ld", &n, &m, &k);
  std::vector<bool> hole(n + 1, 0); // Mark positions where holes exist
  while (m--) {
    long h;
    scanf("%ld", &h);
    hole[h] = 1; // Mark the hole position
  }
  long current(1); // Bone starts at position 1
  while (k--) {
    if (hole[current]) {
      break; // Bone falls into hole, no more swaps
    }
    long u, v;
    scanf("%ld %ld", &u, &v);
    // If bone is at one of the positions being swapped, move it to the other
    if (current == u) {
      current = v;
    } else if (current == v) {
      current = u;
    }
  }
  printf("%ld\n", current);
  return 0;
}


// https://github.com/VaHiX/CodeForces/