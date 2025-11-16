// Problem: CF 1037 A - Packets
// https://codeforces.com/contest/1037/problem/A

/*
Problem: Distribute n coins into minimum number of packets such that any amount from 1 to n can be formed.
Algorithm: Greedy approach based on binary representation.
          - Use powers of 2 (1, 2, 4, 8, ...) as packet sizes until their sum exceeds n.
          - The remaining coins form the last packet.
Time Complexity: O(log n)
Space Complexity: O(1)
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  ll cnt(0); // Count of packets needed
  for (long p = 1; p <= n; p *= 2) { // Iterate through powers of 2
    n -= p; // Deduct current power from total
    ++cnt;  // Increment packet count
  }
  cnt += (n > 0); // Add one more packet if any coins remain
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/