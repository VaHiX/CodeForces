// Problem: CF 845 B - Luba And The Ticket
// https://codeforces.com/contest/845/problem/B

/*
Purpose: 
  This code finds the minimum number of digit replacements needed to make a 6-digit ticket lucky.
  A ticket is lucky if the sum of the first three digits equals the sum of the last three digits.
  
Algorithms/Techniques:
  - Brute-force generation of all possible lucky 6-digit numbers (1 million possibilities).
  - For each lucky number, compute the Hamming distance (number of differing digits) from the input ticket.
  - Track the minimum such distance.

Time Complexity: O(10^6 * 6) = O(10^6) ≈ 10^6 operations
Space Complexity: O(1) - only using a few integer variables, no extra space proportional to input size.

*/
#include <cstdio>

// Check if a 6-digit number is lucky (sum of first 3 digits == sum of last 3)
bool isLucky(long x) {
  int suma(0);
  for (long p = 0; p < 3; p++) {
    suma += x % 10;    // Extract last digit and add to sum
    x /= 10;           // Remove last digit
  }
  int sumb(0);
  for (long p = 0; p < 3; p++) {
    sumb += x % 10;    // Extract last digit and add to sum
    x /= 10;           // Remove last digit
  }
  return (suma == sumb); // Return true if sums are equal
}

// Compute the number of different digits between two 6-digit numbers
int getDist(long a, long b) {
  int count(0);
  for (long p = 0; p < 6; p++) {
    count += ((a % 10) != (b % 10));  // Increment if digits differ
    a /= 10;                          // Remove last digit
    b /= 10;                          // Remove last digit
  }
  return count;
}

int main() {
  long t;
  scanf("%ld", &t);            // Read input ticket as number
  int minDist(10);             // Initialize minimum distance to large value
  for (long p = 0; p < 1000000; p++) {  // Loop through all 6-digit numbers
    if (!isLucky(p)) {         // Skip if not lucky
      continue;
    }
    int dist = getDist(p, t);  // Compute distance to input ticket
    minDist = (dist < minDist) ? dist : minDist; // Update minimum
  }
  printf("%d\n", minDist);     // Print result
  return 0;
}


// https://github.com/VaHiX/CodeForces/