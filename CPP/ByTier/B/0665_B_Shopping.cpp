// Problem: CF 665 B - Shopping
// https://codeforces.com/contest/665/problem/B

/*
B. Shopping
Algorithm: Simulate the process of collecting items from a row where each item's position changes after being picked.
Time Complexity: O(n * m * k) - For each customer (n), we process m items, and for each item we update positions of up to k elements.
Space Complexity: O(k) - A map is used to store positions of k items.

The algorithm maintains a map 'pos' that maps each item to its current position in the row.
For each customer:
    1. Process m items from their order
    2. For each item, get its current position (pos[x])
    3. Add this position to total count
    4. Move the item to front (position = 1)
    5. Update positions of all other items that were earlier than or equal to pos[x]
*/

#include <iostream>
#include <map>
int main() {
  long n, m, k;
  std::cin >> n >> m >> k;
  std::map<int, int> pos; // Maps item to its current position in the row
  for (int p = 1; p <= k; p++) { // Initialize positions according to input
    int x;
    std::cin >> x;
    pos[x] = p;
  }
  long count(0); // Total time counter
  for (int c = 0; c < n; c++) { // Process each customer
    for (int d = 0; d < m; d++) { // Process each item in the customer's order
      int x;
      std::cin >> x;
      int init = pos[x]; // Get current position of item x
      count += init; // Add time taken to find item x
      pos[x] = 1; // Move item x to front (position 1)
      for (int p = 1; p <= k; p++) { // Update positions of all other items
        if (p != x && pos[p] <= init) { // If item p is not x and was located before or at x's original position
          ++pos[p]; // Increment the position since x shifted all previous elements one step right
        }
      }
    }
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/