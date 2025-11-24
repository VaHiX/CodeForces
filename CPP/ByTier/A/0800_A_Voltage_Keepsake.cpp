// Problem: CF 800 A - Voltage Keepsake
// https://codeforces.com/contest/800/problem/A

/*
 * Problem: Voltage Keepsake
 * 
 * Purpose: Determine the maximum amount of time all devices can be used 
 *          simultaneously before one of them runs out of power, given that 
 *          a single charger can be used to charge any one device at a time.
 *
 * Algorithm: Binary search on the answer combined with a greedy feasibility check.
 * 
 * Approach:
 * - Binary search over the time T to find the maximum feasible time.
 * - For a given time T, check if it's possible to keep all devices running.
 * - In the feasibility check, determine how much power must be provided 
 *   by the charger to avoid device depletion.
 *
 * Time Complexity: O(n * log(10^17)) where n is the number of devices.
 * Space Complexity: O(n) for storing device parameters.
 */

#include <cstdio>
#include <vector>

// Check if we can run all devices for 'time' seconds with available charger power 'provided'
bool check(const std::vector<double> &rate, const std::vector<double> &saved,
           const double &provided, double time) {
  double req(0.0);
  for (long p = 0; p < rate.size(); p++) {
    // If device has enough power to last the full time without charging, skip it
    if (saved[p] > rate[p] * time) {
      continue;
    }
    // Amount of power needed to be supplied by charger for this device
    req += (rate[p] - saved[p] / time);
  }
  // If total required power is less than or equal to available charger power
  return (req <= provided);
}

int main() {
  const double eps = 0.00001; // Epsilon for binary search precision
  long n;
  double pow;
  scanf("%ld %lf", &n, &pow);
  std::vector<double> a(n), b(n);
  for (long p = 0; p < n; p++) {
    scanf("%lf %lf", &a[p], &b[p]);
  }
  
  // Calculate total power consumption of all devices
  double sumPower(0);
  for (long p = 0; p < n; p++) {
    sumPower += a[p];
  }
  
  // If total power consumption is less than or equal to the charger power,
  // devices can run indefinitely
  if (sumPower <= pow) {
    puts("-1");
    return 0;
  }
  
  // Binary search bounds
  double left(0), right(1e10 + 1e7);
  
  // Perform binary search
  while (right - left > eps) {
    double mid = (left + right) / 2.0;
    if (check(a, b, pow, mid)) {
      left = mid;  // Feasible, try a longer time
    } else {
      right = mid; // Not feasible, try a shorter time
    }
  }
  
  // Output the maximum feasible time
  printf("%.5lf\n", (left + right) / 2.0);
  return 0;
}


// https://github.com/VaHiX/CodeForces/