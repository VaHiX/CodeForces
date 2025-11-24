// Problem: CF 1209 B - Koala and Lights
// https://codeforces.com/contest/1209/problem/B

/*
B. Koala and Lights
Purpose: Determine the maximum number of lights that will ever be on simultaneously,
         given their initial states and toggle patterns.

Algorithms/Techniques:
- Simulation approach using a 2D array to track light states over time.
- For each light, it toggles every 'a_i' seconds starting from 'b_i'.
- Time complexity: O(n * N) where N = 150 (max time steps simulated)
- Space complexity: O(n * N) for the 2D state array.

Input:
- n: number of lights
- s: initial state string ('1' = on, '0' = off)
- For each light i: a_i and b_i parameters defining toggle pattern

Output:
- Maximum number of lights that are on at any time step
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 150; // Maximum time steps to simulate
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::vector<int> a(n), b(n); // Store parameters for each light
  for (long p = 0; p < n; p++) {
    std::cin >> a[p] >> b[p];
  }
  std::vector<std::vector<int>> f(n, std::vector<int>(N, 0)); // State of lights at each time step
  long mx(0); // Maximum number of lights on at any instant

  // Initialize the first time step
  for (long p = 0; p < n; p++) {
    f[p][0] = (s[p] - '0'); // Convert char to int (1 or 0)
    mx += f[p][0]; // Add initial state to max counter
  }

  // Simulate light states for all time steps up to N
  for (long t = 1; t < N; t++) {
    long cnt(0); // Count of lights on at current time step
    for (long p = 0; p < n; p++) {
      // Check if the light should toggle at this time step (based on a[p] and b[p])
      if ((t >= b[p]) && ((t - b[p]) % a[p] == 0)) {
        f[p][t] = 1 - f[p][t - 1]; // Toggle state
      } else {
        f[p][t] = f[p][t - 1]; // Keep same state
      }
      cnt += f[p][t]; // Add to count of lights on at this time
    }
    mx = (mx > cnt) ? mx : cnt; // Update maximum if current count is higher
  }

  std::cout << mx << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/