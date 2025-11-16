// Problem: CF 847 M - Weather Tomorrow
// https://codeforces.com/contest/847/problem/M

/*
 * Code Purpose: Predicts the temperature for the next day based on Vasya's method.
 *               If the last n days form an arithmetic progression, the next temperature
 *               is the next term in the sequence. Otherwise, it equals the last known
 *               temperature.
 *
 * Algorithm: 1. Read the number of days 'n' and the temperatures for each day.
 *            2. Compute the common difference 'd' from the first two temperatures.
 *            3. Check if all consecutive differences match 'd' to determine if it's an AP.
 *            4. If it's an AP, predict the next term using the formula: last_term + d.
 *            5. If not, predict the next term as the last known temperature.
 *
 * Time Complexity: O(n) - We iterate through the array once to check for arithmetic progression.
 * Space Complexity: O(n) - Space used to store the vector of temperatures.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long d = a[1] - a[0];  // Calculate the common difference of the potential arithmetic progression
  bool progression(true);  // Flag to indicate if the sequence is an arithmetic progression
  for (long p = 1; p < n; p++) {
    if (a[p] - a[p - 1] != d) {  // Check if current difference matches the common difference
      progression = false;
      break;
    }
  }
  printf("%ld\n", a.back() + (progression ? d : 0));  // Predict next temperature based on AP or not
  return 0;
}


// https://github.com/VaHiX/CodeForces/