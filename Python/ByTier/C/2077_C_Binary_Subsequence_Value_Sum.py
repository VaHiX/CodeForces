# Problem: CF 2077 C - Binary Subsequence Value Sum
# https://codeforces.com/contest/2077/problem/C

"""
C. Binary Subsequence Value Sum

Purpose:
This code computes the sum of scores over all non-empty subsequences of a binary string after a series of flips.
The score for a subsequence is defined as the maximum value of F(v, 1, i) * F(v, i+1, |v|) over all valid i,
where F(v, l, r) = (r - l + 1) - 2 * zero(v, l, r).

Algorithms/Techniques:
- Dynamic Programming
- Efficient updates using a counter approach to avoid recomputing full score each time.
- Modular exponentiation for fast power calculations.

Time Complexity: O(n + q)
Space Complexity: O(n)

"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 998244353

for _ in range(int(input())):
    n, q = map(int, input().split())
    s = [int(x) for x in input()]
    # Precompute base res value as 2^(n-4) mod 998244353
    res = pow(2, n - 4, mod)
    # cnt keeps track of the difference between twice number of 1s and total length
    cnt = s.count(1) * 2 - n
    for _ in range(q):
        i = int(input()) - 1  # Convert to 0-based index
        # Flip the bit and update cnt accordingly
        if s[i]:
            cnt -= 2  # Flipping from 1 to 0 reduces count
        else:
            cnt += 2  # Flipping from 0 to 1 increases count
        s[i] = 1 - s[i]
        # Print final result using formula: res * (cnt^2 + n - 2) mod 998244353
        print(res * (cnt**2 + n - 2) % mod)


# https://github.com/VaHiX/codeForces/