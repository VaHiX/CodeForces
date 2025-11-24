// Problem: CF 660 B - Seating On Bus
// https://codeforces.com/contest/660/problem/B

/*
 * Purpose: Determine the order in which passengers will get off a bus,
 *          given the seating arrangement and boarding pattern.
 *
 * Algorithm:
 * 1. The bus has 2*n rows, each with 2 seats (left and right), so total capacity is 4*n.
 * 2. Passengers board in a specific order:
 *    - First, window seats are filled in the pattern: left window, right window, ...
 *    - Then non-window seats are filled in the same pattern.
 * 3. When getting off, passengers exit in the reverse pattern:
 *    - Non-window seats go first (in a specific order),
 *    - Then window seats.
 * 4. The code simulates the boarding order using a vector to track seat assignments,
 *    then outputs the offboarding sequence based on the fixed exit order.
 *
 * Time Complexity: O(m) - We simulate boarding m passengers and then iterate over 4*n seats once.
 * Space Complexity: O(1) - The vector size is fixed as 4*n, and we only use a constant number of extra variables.
 */
#include <iostream>
#include <vector>
int main() {
  long n, m;
  std::cin >> n >> m;
  std::vector<long> seat(4 * n, 0); // Vector to map seat index to passenger number
  long current(1); // Current seat index to assign passenger to (1-based)
  for (long p = 1; p <= m; p++) {
    seat[current] = p; // Assign current passenger to the seat
    current += 2; // Move to next seat in the boarding order (every 2nd seat)
    if (current > 4 * n) { // Wrap around if we exceed the total number of seats
      current %= 4 * n; // Use modulo to wrap to the beginning
      --current; // Adjust since we are working with 1-based indexing
    }
  }
  for (long p = 0; p < 4 * n; p++) {
    if (seat[p] <= 0) {
      continue; // Skip empty seats
    }
    std::cout << seat[p] << " "; // Output the passenger number in offboarding order
  };
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/