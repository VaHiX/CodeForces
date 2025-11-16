// Problem: CF 820 A - Mister B and Book Reading
// https://codeforces.com/contest/820/problem/A

/*
 * Problem: Mister B and Book Reading
 * 
 * Purpose: Calculate the number of days required for Mister B to finish reading a book,
 *          considering increasing reading speed, maximum speed limit, and pages to reread each day.
 * 
 * Algorithms/Techniques:
 *   - Simulation approach: Iteratively simulate each day of reading until the book is finished.
 *   - Speed increases daily by 'a' up to a maximum 'v1'.
 *   - Every day after the first, 'l' pages from the previous day are reread.
 * 
 * Time Complexity: O(√c) in the worst case, as the reading speed grows linearly, so the number of days
 *                    is approximately sqrt(2*c/a) when acceleration is significant.
 * 
 * Space Complexity: O(1), only using a constant amount of variables.
 */

#include <iostream>
int main() {
  long c, v0, v1, a, l;
  std::cin >> c >> v0 >> v1 >> a >> l;
  long read(0), step(v0), days(0); // 'read' tracks total pages read, 'step' is daily reading speed, 'days' counts days
  while (read < c) { // Continue until all pages are read
    if (read > 0) {  // On day 2 and later, reread 'l' pages from previous day
      read -= l;
    }
    read += step;    // Add pages read this day
    step += a;       // Increase reading speed by 'a'
    step = (step < v1) ? step : v1; // Cap the reading speed at 'v1'
    ++days;          // Increment day counter
  }
  std::cout << days << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/