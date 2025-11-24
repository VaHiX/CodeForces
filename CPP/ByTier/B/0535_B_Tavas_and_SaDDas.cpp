// Problem: CF 535 B - Tavas and SaDDas
// https://codeforces.com/contest/535/problem/B

/*
 * Problem: Tavas and SaDDas
 * Purpose: Given a lucky number (consisting only of digits 4 and 7), find its 1-based index
 *          when all lucky numbers are sorted in ascending order.
 *
 * Algorithm:
 * - Lucky numbers can be thought of as binary-like numbers where 4 corresponds to 0 and 7 to 1.
 * - First, we calculate how many lucky numbers have fewer digits than the input number.
 * - Then, we convert the input number into a binary-like representation (0 for 4, 1 for 7)
 *   and compute its rank among same-length lucky numbers.
 *
 * Time Complexity: O(log n) - where log n is the number of digits in n
 * Space Complexity: O(log n) - for storing the digits of n
 */

#include <cstdio>
#include <vector>
int main() {
  long long n;
  scanf("%lld", &n);
  long long m = n;
  long ansA(1), ansB(0);  // ansA counts numbers with fewer digits, ansB is binary-like index
  std::vector<int> digits;
  while (m > 0) {
    ansA *= 2;          // Multiplies by 2 for each digit position (like binary)
    digits.push_back(m % 10);  // Store last digit
    m /= 10;            // Remove last digit
  }
  for (int p = digits.size() - 1; p >= 0; p--) {
    ansB = 2 * ansB + (digits[p] == 7);  // Build binary-like number (7 = 1, 4 = 0)
  }
  long ans = ansA + ansB - 1;  // Total count of all shorter numbers + position in same-length group
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/