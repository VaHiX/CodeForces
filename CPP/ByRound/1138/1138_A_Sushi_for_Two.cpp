// Problem: CF 1138 A - Sushi for Two
// https://codeforces.com/contest/1138/problem/A

/*
 * Problem: A. Sushi for Two
 * Algorithm: Two Pointers / Sliding Window
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * The problem asks to find the longest continuous subsegment where:
 * - Equal number of tuna (1) and eel (2) sushi
 * - Each half contains only one type of sushi
 * 
 * Approach:
 * - Use a sliding window technique to traverse the array
 * - Keep track of the current segment's length and types
 * - When encountering a change in type, check if the previous segment can form a valid subsegment
 * - Update maximum length accordingly
 */

#include <iostream>
int a, b, c, k, m, n, t; // Variables for tracking segments and max length
int main() {
  for (std::cin >> n; n--; // Read input and decrement n
       t ^ k ? a = b, b = 1, k = t : b++, m > (c = a < b ? a : b) ?: m = c) // Main logic for segment handling
    std::cin >> t; // Read next sushi type
  std::cout << m * 2; // Output maximum length (each half contributes to total)
}


// https://github.com/VaHiX/codeForces/