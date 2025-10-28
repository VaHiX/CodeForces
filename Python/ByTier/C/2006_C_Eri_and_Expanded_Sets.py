# Problem: CF 2006 C - Eri and Expanded Sets
# https://codeforces.com/contest/2006/problem/C

"""
Algorithm: 
- For each subarray, we check if it can be expanded to form a consecutive set.
- The key insight is that for a set to be expandable into a consecutive set, 
  the GCD of differences between adjacent elements must be 1 or a power of 2.
- We use a sliding window approach with a data structure to track the GCDs of 
  differences and update the count of valid subarrays accordingly.
- Time Complexity: O(n log M) where n is the length of the array and M is the maximum element.
- Space Complexity: O(n) for storing intermediate results and differences.

Techniques:
- Sliding window with GCD computation
- Bit manipulation to check if a number is a power of 2
"""

import math
import sys


def solve() -> None:
    it = iter(sys.stdin.buffer.read().split())
    t = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it))
        a = [int(next(it)) for _ in range(n)]
        ans = n
        if n == 1:
            out.append(str(ans))
            continue
        # Compute difference array
        d = [abs(a[i + 1] - a[i]) for i in range(n - 1)]
        # cur keeps track of (gcd, count) pairs for current window
        cur = []
        for val in d:
            # Start new list of (gcd, count) pairs
            nxt = [(val, 1)]
            # Process previous pairs and update with new gcd
            for g, cnt in cur:
                ng = math.gcd(g, val)
                if nxt[-1][0] == ng:
                    # If same gcd, increment count
                    nxt[-1] = (ng, nxt[-1][1] + cnt)
                else:
                    # Otherwise add new gcd
                    nxt.append((ng, cnt))
            # Check if current pair (gcd, count) leads to a valid consecutive set
            for g, cnt in nxt:
                if g == 0 or (g & (g - 1)) == 0:
                    # If g is 0 or a power of two, we add count to result
                    ans += cnt
            # Update current list
            cur = nxt
        out.append(str(ans))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/