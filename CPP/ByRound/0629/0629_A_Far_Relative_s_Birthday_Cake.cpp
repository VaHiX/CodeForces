// Problem: CF 629 A - Far Relative’s Birthday Cake
// https://codeforces.com/contest/629/problem/A

/*
 * Code Purpose: 
 *   Calculates the happiness value of Famil Door's birthday cake based on the number of chocolate pairs
 *   that share the same row or column.
 * 
 * Algorithm:
 *   1. For each row, count the number of chocolates ('C') and compute the number of pairs in that row using combination formula C(n,2) = n*(n-1)/2.
 *   2. For each column, maintain a count of chocolates and similarly compute pairs for that column.
 *   3. Sum all row pairs and column pairs to get the total happiness.
 * 
 * Time Complexity: O(n^2), where n is the size of the cake grid.
 * Space Complexity: O(n), due to the vector storing column chocolate counts.
 */

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::vector<long> v(n, 0); // Vector to store number of chocolates in each column
  int64_t total(0); // Variable to store total happiness value
  for (long row = 0; row < n; row++) {
    std::string s;
    std::cin >> s;
    long count(0); // Count of chocolates in current row
    for (long col = 0; col < n; col++) {
      if (s[col] == 'C') {
        ++count;
        ++v[col]; // Increment column count for this column
      }
    }
    // Add number of pairs in this row to total
    total += count * (count - 1) / 2;
  }
  // Add number of pairs in each column to total
  for (long p = 0; p < n; p++) {
    total += v[p] * (v[p] - 1) / 2;
  }
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/