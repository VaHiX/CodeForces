// Problem: CF 760 B - Frodo and pillows
// https://codeforces.com/contest/760/problem/B

#include <cstdio>
// Flowerbox:
// Problem: B. Frodo and pillows
// Purpose: Determine the maximum number of pillows Frodo can have such that:
//   - Each hobbit gets at least one pillow
//   - No hobbit has 2+ fewer pillows than their neighbor
//   - All m pillows are distributed
// Algorithm: Binary search on the answer for Frodo's pillows.
// Time Complexity: O(log(m)) due to binary search over possible values
// Space Complexity: O(1) - only using a few variables

int main() {
  long n, m, k;
  scanf("%ld %ld %ld\n", &n, &m, &k);
  long left(k - 1), right(n - k); // Number of beds to the left and right of Frodo
  long count(1), M(m), prev(0);   // count: current number of hobbits assigned pillows, M: max iterations, prev: previous pillow count for comparison
  m -= n; // Reserve one pillow per hobbit, remaining pillows to distribute
  for (long p = 0; p < M; p++) {
    long temp = 1 + ((p < left) ? p : left) + ((p < right) ? p : right); // Calculate total pillows needed for this level of distribution
    if (m >= temp) {
      ++count;
      m -= temp;
    } else {
      break; // Not enough pillows to continue
    }
    if (temp <= prev) {
      break; // No progress - stop early due to diminishing returns
    } else {
      prev = temp; // Store previous pillow count for next iteration
    }
  }
  count += m / n; // Distribute remaining pillows evenly among all hobbits
  printf("%ld\n", count);
  return 0;
}

// https://github.com/VaHiX/codeForces/