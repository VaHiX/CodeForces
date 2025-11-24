// Problem: CF 896 B - Ithea Plays With Chtholly
// https://codeforces.com/contest/896/problem/B

/*
 * Code Purpose: This program helps Chtholly win a game against Ithea by choosing
 *               the correct paper sheet to write each number such that all sheets
 *               eventually form a non-decreasing sequence.
 *
 * Algorithm: The approach uses a greedy strategy based on the value of the number
 *            given. If the number is small (<= c/2), it tries to place it in the
 *            leftmost valid position that maintains non-decreasing order. If the
 *            number is large (> c/2), it tries to place it in the rightmost valid
 *            position. This greedy strategy works because placing large numbers
 *            on the right helps maintain the order, and vice versa.
 *
 * Time Complexity: O(n * m) in the worst case, where we might need to traverse
 *                  the array for each of the m rounds.
 *
 * Space Complexity: O(n) for storing the state of the n sheets.
 */

#include <cstdio>
#include <vector>

int main() {
  long n, m, c;
  scanf("%ld %ld %ld", &n, &m, &c);
  std::vector<long> a(n, 0); // Vector to store the value in each sheet, initialized to 0
  long rem(n);               // Number of empty sheets remaining
  long pos(0);               // Current position to possibly place the number

  while (rem) {              // Continue until all sheets are filled
    long x;
    scanf("%ld", &x);        // Read the number given by Ithea

    if (2 * x <= c) {        // If number is small or medium (<= c/2)
      pos = 0;
      // Find the leftmost position where x can be placed to maintain non-decreasing order
      while (a[pos] && a[pos] <= x) {
        ++pos;
      }
    } else {                 // If the number is large (> c/2)
      pos = n - 1;
      // Find the rightmost position where x can be placed to maintain non-decreasing order
      while (a[pos] && a[pos] >= x) {
        --pos;
      }
    }

    // Decrement the count of remaining empty sheets if this position was previously empty
    rem -= (a[pos] == 0);
    a[pos] = x;              // Place the number in the chosen sheet
    printf("%ld\n", pos + 1); // Output the sheet number (1-indexed)
    fflush(stdout);          // Flush the output buffer
  }

  return 0;
}


// https://github.com/VaHiX/CodeForces/