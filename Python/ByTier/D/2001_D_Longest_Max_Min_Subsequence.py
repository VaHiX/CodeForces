# Problem: CF 2001 D - Longest Max Min Subsequence
# https://codeforces.com/contest/2001/problem/D

"""
D. Longest Max Min Subsequence

Algorithm:
This problem is about finding the longest subsequence from a given sequence such that:
1. The subsequence should be ordered in a way to maximize the "max-min" property.
2. If there are multiple such subsequences of same length, return the lexicographically smallest one after multiplying elements at odd positions by -1.

The approach uses a stack-based greedy algorithm with a monotonic property:
- Process elements from left to right in the sequence
- For each element, maintain a stack that respects certain ordering rules
- When adding an element:
    - Remove elements from the stack if the new arrangement is lexicographically better (based on odd position multiplication)
    - Update the count of remaining elements to determine when elements can be safely removed

Time Complexity: O(n)
Space Complexity: O(n)

Reference:
This problem leverages greedy stack-based algorithms like those seen in "next greater element" or LIS variations.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def II(base=10):
    return int(input(), base)


def LI():
    return list(map(int, input()))


def LII():
    return list(map(int, input().split()))


def main():
    n = II()
    A = LII()
    ct = [0] * (n + 1)  # Count of remaining occurrences for each value
    for a in A:
        ct[a] += 1
    sk = []  # Stack to maintain the result subsequence
    vis = [0] * (n + 1)  # Track if element is already in stack
    for a in A:
        ct[a] -= 1  # Decrement the count as we process this element
        if vis[a]:
            continue  # Skip if already in stack
        # While stack is not empty and we can remove elements to satisfy ordering
        while sk and ct[sk[-1]]:
            w = len(sk)
            # Check if removing top of stack improves lexicographical order,
            # considering that odd elements are negated.
            if (w & 1 and sk[-1] < a) or (w & 1 ^ 1 and sk[-1] > a):
                vis[sk.pop()] = 0
            elif (
                w > 1
                and ct[sk[-2]]
                and ((w & 1 and sk[-2] > a) or (w & 1 ^ 1 and sk[-2] < a))
            ):
                # Remove two elements from stack if beneficial
                vis[sk.pop()] = 0
                vis[sk.pop()] = 0
            else:
                break
        sk.append(a)
        vis[a] = 1
    print(len(sk))
    print(*sk)


for _ in range(II()):
    main()


# https://github.com/VaHiX/codeForces/