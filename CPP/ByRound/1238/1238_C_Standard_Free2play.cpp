// Problem: CF 1238 C - Standard Free2play
// https://codeforces.com/contest/1238/problem/C

/*
C. Standard Free2play
Problem Description:
You are on a cliff of height h, with platforms at each height 1 to h. Some platforms are initially moved out (visible), and others are hidden.
The character starts on the platform at height h.
When standing on a moved-out platform at height x, you can pull a lever that switches the state of both:
   - Current platform (x) -> hides
   - Platform below (x-1) -> toggles state (if it was moved out, now hidden; if hidden, now moved out)
This is the only way to move between platforms.
The character can safely fall from height x to height x-2 but not further.
You can buy magic crystals to change the state of any platform (except height h).
Goal: Find minimum number of crystals needed to reach ground level (0).

Approach:
Use a greedy simulation with a queue:
1. Process platforms in descending order from h down to 1
2. When on a platform, choose the best way to move down based on safety constraint (max fall of 2)
3. If necessary, use crystals to ensure safe passage

Time Complexity: O(n) where n is number of platforms (sum over queries)
Space Complexity: O(n) for the queue and array storing platforms
*/

#include <stdio.h>
#include <algorithm>
#include <queue>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010101
#define inf 1e18
#define mod 998244353
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m, q, h;
  sf(q); // Read number of test cases
  while (q--) {
    sff(h, n); // Read height and number of moved out platforms
    queue<int> q_platform; // Queue to simulate platforms
    int a[n + 1]; // Array to store platform heights
    for (i = 0; i < n; i++)
      sf(a[i]), q_platform.push(a[i]); // Read platform heights
    q_platform.push(0); // Add ground level as a sentinel
    a[n] = 0; // Mark ground as hidden

    int ans = 0; // Count of magic crystals needed
    q_platform.pop(); // Remove first entry (we'll process from current position)

    while (!q_platform.empty() && h > 0) {
      k = q_platform.front(); // Current platform height
      
      if (h - k >= 2) // If we can safely fall two steps without crystal use
        h = k + 1; // Move up to next available platform
      else {
        q_platform.pop(); // Remove current platform from queue
        if (h - q_platform.front() > 2) { // Need crystal if falling more than 2 units
          ans++; // Buy one crystal
        } else {
          q_platform.pop(); // No crystal needed, just continue to next platform
        }
        h -= 2; // Move down two levels due to gravity
      }
    }
    
    pf(ans); // Output result
    nl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/