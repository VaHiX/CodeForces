# Problem: CF 1772 C - Different Differences
# https://codeforces.com/contest/1772/problem/C

"""
Algorithm: Constructing a strictly increasing array with maximum characteristic
Techniques: Greedy approach, Set usage for uniqueness

Time Complexity: O(k + n) per test case, where k is the size of array and n is the upper bound.
Space Complexity: O(k + n) for storing the array and set.

The approach:
1. Start with the smallest element 1.
2. For each next element, try to add the smallest possible difference (starting from 1) such that the resulting element is within the range [1, n].
3. After building the initial sequence, try to add elements from n down to 1 to fill up the array, ensuring all elements remain unique.
4. Output the sorted result.
"""

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    k, n = map(int, input().split())

    ANS = [1]  # Start with the smallest possible value
    now = 1    # Current difference to use

    for i in range(k - 1):
        if len(ANS) == k:  # Stop if we have enough elements
            break
        if ANS[-1] + now <= n:  # If adding current difference keeps it within range
            ANS.append(ANS[-1] + now)
            now += 1  # Increment difference for next step
        else:
            break

    S = set(ANS)  # Use set to track unique values

    for i in range(n, -1, -1):  # Try to add elements from n down to 1
        if len(S) == k:  # Stop if we already have k elements
            break
        S.add(i)  # Add element if not already present

    print(*sorted(S))  # Output the sorted unique elements


# https://github.com/VaHiX/CodeForces/