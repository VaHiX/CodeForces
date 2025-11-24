// Problem: CF 834 A - The Useless Toy
// https://codeforces.com/contest/834/problem/A

/*
 * Code Purpose: Determine the direction (clockwise or counter-clockwise) of a spinning
 *               V-shaped caramel spinner given its start and end positions, and the
 *               duration of rotation.
 *
 * Algorithm: The spinner cycles through 4 positions: 'v', '<', '^', '>'. The rotation
 *            is modeled by advancing the index in either direction. For a given duration,
 *            we compute both possible final positions (clockwise and counter-clockwise)
 *            and compare with the actual ending position to determine the direction.
 *
 * Time Complexity: O(1) - The number of operations is constant, as the loop depends
 *                      on the modulo of n with 4, which is bounded.
 *
 * Space Complexity: O(1) - Only a fixed amount of variables are used regardless of input size.
 */

#include <iostream>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  char ch1, ch2;
  cin >> ch1 >> ch2;  // Read starting and ending positions
  cin >> n;
  n = n % 4;  // Reduce n to a meaningful value within 0-3 since the pattern repeats every 4 steps
  string s = "v<^>";  // Define the sequence of positions in order
  char cw, ccw;  // Variables to store the computed end positions for cw and ccw rotations

  // Find the index of the starting position in the sequence
  for (i = 0; i < 4; i++) {
    if (s[i] == ch1) {
      j = i;
      break;
    }
  }

  i = j;  // Reset i to the starting index
  k = n;  // Reset k to n for clockwise calculation
  // Simulate clockwise rotation
  while (k--) {
    i++;
    i = i % 4;  // Wrap around the index
  }
  cw = s[i];  // The resulting position after clockwise rotation

  i = j;  // Reset i to the starting index
  k = n;  // Reset k to n for counter-clockwise calculation
  // Simulate counter-clockwise rotation
  while (k--) {
    i--;
    if (i < 0)
      i = 3;  // Wrap around the index if it goes below 0
  }
  ccw = s[i];  // The resulting position after counter-clockwise rotation

  // Determine the direction based on comparison
  if (cw == ccw)
    cout << "undefined";  // If both directions lead to same end, it's uncertain
  else if (cw == ch2)
    cout << "cw";  // If clockwise matches the actual end, it's clockwise
  else if (ccw == ch2)
    cout << "ccw";  // If counter-clockwise matches the actual end, it's counter-clockwise
  else
    cout << "undefined";  // In case of mismatch, output undefined (should not happen due to problem guarantees)

  return 0;
}


// https://github.com/VaHiX/CodeForces/