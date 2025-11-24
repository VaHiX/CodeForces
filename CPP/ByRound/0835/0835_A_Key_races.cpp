// Problem: CF 835 A - Key races
// https://codeforces.com/contest/835/problem/A

/*
 * Problem: Key races
 * Algorithm/Technique: Simulation of competition timing
 * 
 * The competition involves two participants typing a text with given typing speeds and pings.
 * For each participant:
 *   1. Wait for ping time (t) to receive the text
 *   2. Type all characters (s * v) 
 *   3. Wait for ping time (t) to transmit result
 * Total time for participant = s * v + 2 * t
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only a few integer variables used
 */

#include <cstdio>
int main() {
  long s, v1, v2, t1, t2;
  scanf("%ld %ld %ld %ld %ld", &s, &v1, &v2, &t1, &t2);
  long a = s * v1 + 2 * t1;  // Total time for first participant
  long b = s * v2 + 2 * t2;  // Total time for second participant
  if (a == b) {
    puts("Friendship");
  } else {
    puts((a < b) ? "First" : "Second");  // Compare and output winner
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/