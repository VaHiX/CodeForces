// Problem: CF 670 B - Game of Robots
// https://codeforces.com/contest/670/problem/B

/*
 * Problem: B. Game of Robots
 * 
 * Algorithm/Technique: Simulation with mathematical optimization
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Description:
 * Robots say identifiers in a specific pattern. The first robot says its identifier,
 * the second says the first robot's identifier and then its own, and so on.
 * The task is to find the k-th identifier spoken.
 * 
 * Approach:
 * We simulate the process but use a mathematical trick to avoid generating
 * all values explicitly. Instead, we calculate how many numbers are spoken
 * at each step and subtract from k until we find which robot contributes
 * the k-th number.
 * 
 * Key insight:
 * - At step i (1-indexed), robot i says i identifiers.
 * - So the first robot speaks 1 number, second robot speaks 2, ..., nth robot speaks n.
 * - To find the k-th number, we keep reducing k by the number of identifiers 
 *   each robot contributes, until k becomes within the range of a specific robot.
 * 
 * Example:
 * For n=4, k=5:
 * - Robot 1 says 1 number (1)
 * - Robot 2 says 2 numbers (1, 4)
 * - Robot 3 says 3 numbers (1, 4, 18)
 * - Robot 4 says 4 numbers (10, 4, 18, 3)
 * The sequence is: 10, 10, 4, 10, 4, 18, 10, 4, 18, 3
 * So, k=5 corresponds to 4 (second number from robot 2).
 */

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, kb;
  cin >> n >> k;
  ll a[n]; // Store identifiers of robots
  kb = k;  // Copy k to kb to avoid modifying original k
  for (i = 0; i < n; i++)
    cin >> a[i];
  j = 1;   // j represents the current robot index (1-based)
  while (true) {
    if (kb - j > 0) {      // If remaining k is greater than current robot's count
      kb -= j;             // Reduce k by the number of identifiers this robot speaks
      j++;                 // Move to next robot
    } else {
      cout << a[kb - 1] << endl; // Output the k-th identifier (0-based index)
      break;                   // Exit loop
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/