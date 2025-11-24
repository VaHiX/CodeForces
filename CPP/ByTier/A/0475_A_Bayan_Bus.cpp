// Problem: CF 475 A - Bayan Bus
// https://codeforces.com/contest/475/problem/A

/*
 * Purpose: This program simulates the seating arrangement of participants on a bus
 *          for the Bayan Programming Contest. The bus has a specific layout with
 *          34 seats, and participants fill seats from left to right in the last row,
 *          then proceed to other rows as needed. The output is a visual representation
 *          showing which seats are occupied ('O') and which are empty ('#').
 *
 * Algorithms/Techniques:
 *   - Direct simulation of seating based on input
 *   - Simple iteration through predefined row structures to assign seats
 *   - Logical assignment of seats in a fixed bus layout
 *
 * Time Complexity: O(k), where k is the number of participants (at most 34).
 * Space Complexity: O(1), as the space used is constant regardless of input size.
 */

#include <iostream>
#include <string>

int main() {
  // Define the bus structure using strings
  std::string top = "+------------------------+\n";
  std::string first = "|#.#.#.#.#.#.#.#.#.#.#.|D|)\n";   // First row of seats
  std::string second = "|#.#.#.#.#.#.#.#.#.#.#.|.|\n";  // Second row of seats
  std::string aisle = "|#.......................|\n";   // Aisle row (with 4 seats)
  std::string third = "|#.#.#.#.#.#.#.#.#.#.#.|.|)\n";  // Third row of seats
  std::string bottom = "+------------------------+";      // Bottom border of bus

  int k;
  std::cin >> k;  // Read number of participants

  // Handle the special case of the aisle row (first 3 participants)
  if (k >= 3) {
    aisle[1] = 'O';  // Assign first seat in aisle to a participant
    --k;
  }

  int a, b, c;  // Indexes to track placement in each row
  a = b = c = 1;  // Start placing seats at index 1 (skip initial delimiter)

  // Assign seats in round-robin fashion across rows
  while (k > 0) {
    first[a] = 'O';  // Assign to first row
    a += 2;          // Move to next seat (skip delimiter)
    --k;
    if (!k) break;

    second[b] = 'O';  // Assign to second row
    b += 2;
    --k;
    if (!k) break;

    third[c] = 'O';   // Assign to third row
    c += 2;
    --k;
    if (!k) break;
  }

  // Output the complete bus layout
  std::cout << top << first << second << aisle << third << bottom;
  return 0;
}


// https://github.com/VaHiX/CodeForces/