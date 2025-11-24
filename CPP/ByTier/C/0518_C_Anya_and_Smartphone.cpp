// Problem: CF 518 C - Anya and Smartphone
// https://codeforces.com/contest/518/problem/C

/*
 * Problem: Anya and Smartphone
 * 
 * Purpose: 
 *   Calculates the total number of gestures required to launch a sequence of applications
 *   on a smartphone with a specific screen layout and dynamic icon rearrangement.
 * 
 * Algorithms/Techniques:
 *   - Simulation with efficient position tracking using arrays
 *   - Moving elements in a permutation to the front after each use
 * 
 * Time Complexity:
 *   O(n + m * k) where n is the number of applications, m is the number of launches,
 *   and k is the number of icons per screen. In worst case, for each launch, we may
 *   need to update positions up to k times due to swapping, but average is lower.
 * 
 * Space Complexity:
 *   O(n) for storing app positions and indices.
 */

#include <cstdio>
#include <vector>
int main() {
  long long n, m, k;
  scanf("%lld %lld %lld\n", &n, &m, &k);
  std::vector<long long> app(n), pos(n); // app[i] stores the app id at position i; pos[i] stores the position of app i
  for (long long p = 0; p < n; p++) {
    long long temp;
    scanf("%lld", &temp);
    app[p] = temp - 1; // Convert to 0-based indexing
    pos[temp - 1] = p; // Position of app temp-1 is p
  }
  long long count(0); // Total gestures count
  while (m--) { // For each application to be launched
    long long currentApp;
    scanf("%lld\n", &currentApp);
    --currentApp; // Convert to 0-based indexing
    long long currentPos = pos[currentApp]; // Find current position of this app
    count += (1 + (currentPos / k)); // Add gestures needed to scroll to screen and press the app
    if (currentPos == 0) {
      continue; // No swap if it's already at the front
    }
    long long previousApp = app[currentPos - 1]; // App that comes before current app
    app[currentPos - 1] = currentApp; // Swap: move current app one position left
    app[currentPos] = previousApp; // And put previous app at current position
    --pos[currentApp]; // Update positions in the array
    ++pos[previousApp];
  }
  printf("%lld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/