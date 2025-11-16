// Problem: CF 792 B - Counting-out Rhyme
// https://codeforces.com/contest/792/problem/B

/*
Purpose: This code simulates a counting-out game among n children arranged in a circle. 
         For each of k steps, a leader counts a_i positions clockwise and eliminates the child at that position.
         The next child after the eliminated one becomes the new leader.
         The simulation uses a circular array to track active children.

Algorithms/Techniques:
- Circular array simulation
- Modular arithmetic for cyclic counting
- Linear search for next active child

Time Complexity: O(n * k)
Space Complexity: O(n)

*/
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, t, p;
  cin >> n >> k;
  ll a[k];
  for (i = 0; i < k; i++)
    cin >> a[i];
  ll peep[n]; // Array to mark whether a child is still in the game (1 = active, 0 = eliminated)
  for (i = 0; i < n; i++)
    peep[i] = 1;
  i = 0;        // Step counter
  m = n;        // Number of active children
  p = 1;        // Current leader's index (1-based)
  while (k) {
    t = a[i] % m; // Number of steps to count (mod number of active children)
    if (!t) {
      // If count is divisible by number of active children, eliminate the last one
      cout << p << " ";
      peep[p - 1] = 0; // Mark as eliminated
      m--;
      p--;             // Decrement p to find the next candidate
      while (true) {   // Find next active child
        p++;
        p = p % n;
        if (peep[p])
          break;
      }
      p++; // Increment to make it 1-based
    }
    while (t) {        // Perform the counting
      p = p % n;       // Wrap around the circle
      if (peep[p])     // If current child is active, decrement count
        t--;
      if (!t) {        // If count reaches zero, eliminate this child
        peep[p] = 0;   // Mark as eliminated
        cout << (p + 1) << " "; // Output the eliminated child's number (1-based)
        m--;           // Reduce number of active children
        while (true) { // Find next active child to be the new leader
          p++;
          p = p % n;
          if (peep[p])
            break;
        }
      }
      p++; // Move to the next child
    }
    i++;   // Move to next step
    k--;   // Decrement remaining steps
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/