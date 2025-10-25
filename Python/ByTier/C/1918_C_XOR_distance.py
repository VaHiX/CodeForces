# Problem: CF 1918 C - XOR-distance
# https://codeforces.com/contest/1918/problem/C

"""
Algorithm: XOR-distance
Techniques: Bit manipulation, greedy approach

Time Complexity: O(log(max(a, b, r))) = O(60) since numbers are up to 10^18
Space Complexity: O(1)

The problem asks to minimize |(a⊕x)−(b⊕x)| for all x in [0, r].
We use a greedy bit-by-bit approach:
1. If a < b, swap them so that a >= b.
2. Compute the difference 'diff' = a - b.
3. For each bit position from high to low:
   - If the current bit contributes to diff and we can adjust it using x ≤ r:
     - Reduce diff by 2 * bit_value if possible.
4. Return the minimized diff.

This greedy approach works because we try to "cancel out" bits that contribute
to the difference by choosing x appropriately.
"""

import sys


def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        a, b, r = map(int, input().split())
        if a < b:
            a, b = b, a
        diff = a - b
        i = 1 << 60  # Start with the highest bit (60th bit for 10^18)
        while i:
            # Check if the current bit contributes to diff and can be adjusted
            if diff > 2 * i and a & i and (not b & i) and r >= i:
                diff -= i * 2  # Reduce diff by 2 * i (cancel out the bit)
                r -= i         # Decrease remaining r
            i >>= 1  # Move to the next lower bit
        print(diff)


main()


# https://github.com/VaHiX/CodeForces/