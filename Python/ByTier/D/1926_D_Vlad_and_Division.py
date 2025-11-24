# Problem: CF 1926 D - Vlad and Division
# https://codeforces.com/contest/1926/problem/D

"""
Algorithm/Technique: Greedy with Bit Manipulation
Time Complexity: O(n), where n is the number of elements in the input array.
Space Complexity: O(n), due to the use of a hash map (dictionary) to store counts.

This problem requires grouping numbers such that no two numbers in the same group share 
any bit position (from 1st to 31st) in common. The key insight is that if two numbers 
have differing bits at every position, they can be grouped together. 

We use a greedy approach:
- For each number, we compute its "complement" (flip all 31 bits).
- If the number has not been seen before, we assign it to a new group and mark its complement.
- If the number has already been seen, we reduce the count of that number in the map (indicating reuse from previous group).

This ensures groups are minimized and every number is assigned exactly once.
"""

import sys

input = sys.stdin.readline


def solve(a):
    hv = (1 << 31) - 1  # All 31 bits set to 1
    c = 0
    dct = {}
    for num in a:
        dup = hv ^ num  # Bitwise complement of num (flip all 31 bits)
        if dct.get(num, 0) == 0:  # If we haven't seen this number before
            c += 1  # Start a new group
            dct[dup] = dct.get(dup, 0) + 1  # Mark its complement as used
        else:
            dct[num] -= 1  # Reduce count of this number (reuse from existing group)
    return c


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(solve(a))


# https://github.com/VaHiX/CodeForces/