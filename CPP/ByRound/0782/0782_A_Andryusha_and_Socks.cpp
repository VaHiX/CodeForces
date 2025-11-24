// Problem: CF 782 A - Andryusha and Socks
// https://codeforces.com/contest/782/problem/A

/*
Code Purpose:
This program determines the maximum number of socks that were on the table at the same time during Andryusha's process of organizing socks into pairs. 
It uses a greedy approach where each sock is either placed on the table (if its pair is not yet taken out) or removed from the table (if its pair is already taken out and placed in the wardrobe).

Algorithms/Techniques:
- Simulation of sock retrieval and pairing
- Bit manipulation for tracking presence of a sock's pair
- Single pass through the input sequence

Time Complexity: O(n), where n is the number of pairs (2n total socks)
Space Complexity: O(n), for the array 'a' tracking sock pairs
*/

#include <cstdio>
int n, t, a[200000], c, m;
int main() {
  scanf("%d", &n);
  n <<= 1; // Multiply n by 2 to represent total number of socks
  while (n--) {
    scanf("%d", &t);
    c += a[t] ? -1 : 1; // If pair already exists on table (-1), otherwise add 1
    m = m > c ? m : c;  // Update maximum number of socks on table
    a[t] ^= 1;          // Toggle the presence of the sock pair (0 or 1)
  }
  printf("%d", m);
}


// https://github.com/VaHiX/CodeForces/