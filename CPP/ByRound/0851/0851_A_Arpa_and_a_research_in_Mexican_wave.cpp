// Problem: CF 851 A - Arpa and a research in Mexican wave
// https://codeforces.com/contest/851/problem/A

/*
 * Problem: Arpa and a research in Mexican wave
 * 
 * Purpose: Calculate the number of spectators standing at a given time `t` in a Mexican wave.
 *          The wave process involves spectators standing one by one until `k` spectators are standing,
 *          then the first spectator sits while the next one stands, etc., until all spectators have stood.
 * 
 * Algorithm:
 *   - The process is divided into three phases:
 *     1. From t = 1 to t = k: Each new spectator stands, so the number of standing spectators = t.
 *     2. From t = k+1 to t = n: The wave is fully formed, so exactly k spectators are standing.
 *     3. From t = n+1 to t = n+k: The wave starts to fade, the first spectator sits, etc.
 * 
 * Time Complexity: O(1) - Only a few conditional checks and arithmetic operations.
 * Space Complexity: O(1) - Uses only a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long n, k, t;
  scanf("%ld %ld %ld\n", &n, &k, &t);
  long ans(0);  // Initialize answer variable
  
  // Case 1: If t <= k, the number of standing spectators is equal to the time t
  if (t <= k) {
    ans = t;
  } 
  // Case 2: If t <= n, the wave is fully formed and k spectators are standing
  else if (t <= n) {
    ans = k;
  } 
  // Case 3: If t <= n + k, the wave is fading. The number of standing spectators decreases as time increases.
  else if (t <= n + k) {
    ans = n + k - t;
  }
  
  // Ensure the result doesn't exceed the total number of spectators
  ans = (ans < n) ? ans : n;
  
  printf("%ld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/