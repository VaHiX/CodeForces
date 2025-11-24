// Problem: CF 452 D - Washer, Dryer, Folder
// https://codeforces.com/contest/452/problem/D

/*
 * Problem: Washer, Dryer, Folder
 * Purpose: Find the minimum time to wash, dry, and fold all pieces of laundry
 *          given limited machines for each process.
 *
 * Algorithm:
 * - Use dynamic programming with a vector `dv` where `dv[i]` represents the earliest
 *   time when the i-th piece of laundry can be completed.
 * - For each piece of laundry, we update its completion time based on:
 *   - When it can be washed (after previous washing machine becomes free)
 *   - When it can be dried (after previous drying machine becomes free)
 *   - When it can be folded (after previous folding machine becomes free)
 * - The final answer is the completion time of the last piece plus time to wash,
 *   dry, and fold that piece.
 *
 * Time Complexity: O(k * (n1 + n2 + n3)) = O(k * max(n1, n2, n3))
 * Space Complexity: O(k)
 */
#include <cstdio>
#include <vector>
int main() {
  long k, n1, n2, n3, t1, t2, t3;
  scanf("%ld %ld %ld %ld %ld %ld %ld", &k, &n1, &n2, &n3, &t1, &t2, &t3);
  std::vector<long> dv(k, 0);  // dv[i] = earliest time when i-th piece completes its process
  for (int p = 0; p < k; p++) {
    if (p >= n1) {
      // Update the time when this piece finishes washing,
      // considering that we wait until a washing machine becomes free
      dv[p] = (dv[p] > dv[p - n1] + t1) ? dv[p] : (dv[p - n1] + t1);
    }
    if (p >= n2) {
      // Update the time when this piece finishes drying,
      // considering that we wait until a drying machine becomes free
      dv[p] = (dv[p] > dv[p - n2] + t2) ? dv[p] : (dv[p - n2] + t2);
    }
    if (p >= n3) {
      // Update the time when this piece finishes folding,
      // considering that we wait until a folding machine becomes free
      dv[p] = (dv[p] > dv[p - n3] + t3) ? dv[p] : (dv[p - n3] + t3);
    }
  }
  // Add final processing time (t1 + t2 + t3) to the last item's completion time
  printf("%ld\n", dv.back() + t1 + t2 + t3);
  return 0;
}


// https://github.com/VaHiX/CodeForces/