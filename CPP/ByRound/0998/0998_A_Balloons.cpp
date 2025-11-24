// Problem: CF 998 A - Balloons
// https://codeforces.com/contest/998/problem/A

/*
Code Purpose:
This program solves the problem of dividing packets of balloons between Grigory and Andrew such that:
1. All packets are distributed (no packet is left undistributed).
2. Each person gets at least one packet.
3. The total number of balloons each person gets is not equal.
The approach is to check for a single packet that, if given to one person, ensures that the remaining packets can be given to the other person such that their totals are unequal.

Algorithms/Techniques:
- Greedy approach with a single pass to find a suitable packet.

Time Complexity: O(n), where n is the number of packets.
Space Complexity: O(n), for storing the packet sizes.

*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  long sum(0);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    sum += a[p];
  }
  long ind(-1);
  for (long p = 0; p < n; p++) {
    // Check if giving packet p to one person leaves a distribution such that the two totals are not equal
    if ((2 * a[p] != sum) && (a[p] != sum)) {
      ind = p;
      break;
    }
  }
  if (ind < 0) {
    puts("-1");
  } else {
    printf("1\n%ld\n", ind + 1);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/