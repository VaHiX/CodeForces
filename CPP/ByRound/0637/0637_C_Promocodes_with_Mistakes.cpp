// Problem: CF 637 C - Promocodes with Mistakes
// https://codeforces.com/contest/637/problem/C

/*
C. Promocodes with Mistakes
Purpose: Given n 6-digit promo codes, find the maximum k such that any code can be uniquely identified if entered with at most k errors.
Algorithm: For each pair of promo codes, compute the minimum number of errors needed to transform one into another. The result k is the minimum of these values across all pairs.
Time Complexity: O(n^2 * K), where n is number of codes and K=6 is fixed length of codes.
Space Complexity: O(n * K) for storing the codes.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int K = 6; // Length of each promo code
  int n;
  std::cin >> n;
  std::vector<std::string> a(n);
  for (int p = 0; p < n; p++) { // Read all promo codes
    std::cin >> a[p];
  }
  int k = K; // Initialize k to maximum possible value (6)
  for (int p = 0; p < n; p++) { // For each code
    for (int q = p + 1; q < n; q++) { // Compare with all subsequent codes
      int count(0); // Count of differing positions
      for (int r = 0; r < K; r++) { // Check each digit position
        count += (a[p][r] != a[q][r]); // Increment if digits differ
      }
      int test = (count - 1) / 2; // Minimum errors needed to distinguish
      k = (k < test) ? k : test; // Update k with minimum value found so far
    }
  }
  std::cout << k << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/