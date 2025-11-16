// Problem: CF 685 A - Robbers' watch
// https://codeforces.com/contest/685/problem/A

/*
 * Problem: Robbers' watch
 * 
 * Purpose:
 *   This program calculates the number of valid time pairs (hours, minutes) such that
 *   all digits displayed on the robbers' watches are distinct. The watches use a base-7
 *   numeral system, with hours and minutes having sufficient digits to represent their
 *   respective ranges [0, n-1) and [0, m-1). The watch digits are padded with leading zeros
 *   if necessary.
 *
 * Algorithm:
 *   - Determine the number of digits needed to represent max(n-1) and max(m-1) in base 7.
 *   - Generate all permutations of digits 0..6.
 *   - For each permutation, split into two parts:
 *     - First part represents hours (X digits).
 *     - Second part represents minutes (Y digits).
 *   - Check if the resulting hour and minute values are within valid ranges.
 *   - Count valid combinations.
 *
 * Time Complexity:
 *   O(B! * (X + Y)) where B = 7, X and Y are the number of digits needed for hours and minutes.
 *   The factorial term arises from generating permutations; (X + Y) is the digit conversion cost.
 *   
 * Space Complexity:
 *   O(B) for storing the digit vector (B = 7).
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const int B = 7;  // Base of the numeral system used by robbers' watches
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  
  // Calculate number of digits needed to represent numbers from 0 to n-1 in base 7
  long X(1);
  for (int p = B; p < n; p *= B) {
    ++X;
  }
  
  // Calculate number of digits needed to represent numbers from 0 to m-1 in base 7
  long Y(1);
  for (int p = B; p < m; p *= B) {
    ++Y;
  }
  
  // If total digits required exceeds base 7, it's impossible to have distinct digits
  if (X + Y > B) {
    puts("0");
    return 0;
  }
  
  // Create a vector of digits 0 to B-1 for generating permutations
  std::vector<int> v(B, 0);
  for (int p = 0; p < B; p++) {
    v[p] = p;
  }
  
  long count(0);  // Counter for valid time pairs
  do {
    // Convert first X digits into hour value
    long a(0);
    for (long p = 0; p < X; p++) {
      a = a * B + v[p];
    }
    
    // Convert next Y digits into minute value
    long b(0);
    for (long p = X; p < X + Y; p++) {
      b = B * b + v[p];
    }
    
    // Check if the hour and minute values are within valid ranges
    count += (a < n) && (b < m);
  } while (next_permutation(v.begin(), v.end()));  // Generate next permutation
  
  // Adjust for overcounting due to unused digits (not directly needed for correctness)
  // This section appears to be a bug or redundant operation; it does not affect correctness based on original problem
  for (int p = 0; p < B - X - Y; p++) {
    count /= (p + 1);
  }
  
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/