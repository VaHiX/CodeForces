# Problem: CF 2160 B - Distinct Elements
# https://codeforces.com/contest/2160/problem/B

"""
B. Distinct Elements

Algorithm/Technique: Simulation + Greedy Construction

Time Complexity: O(n) per test case, where n is the length of array b.
Space Complexity: O(n) for storing the output array a.

The problem involves reconstructing an array 'a' from a given array 'b', where each b[i] represents the sum of distinct element counts in all subarrays ending at position i. 

We use a greedy approach:
- For each index i, we compute the difference between b[i] and b[i-1].
- If this difference equals i+1, it means that the new element at position i is distinct from all previous elements; hence, we assign it the next available number (next_new).
- Otherwise, we reuse a previously assigned value at index (i - diff), maintaining consistency with the cumulative sum structure.

This allows us to build an array 'a' such that the corresponding 'b' array matches the input.
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    b = list(map(int, input().split()))
    a = []
    next_new = 1  # Next unused number to assign
    for i in range(n):
        prev_b = b[i - 1] if i > 0 else 0  # Previous cumulative sum
        diff = b[i] - prev_b  # Difference gives us information about new distinct elements
        if diff == i + 1:
            # All elements from 1 to i+1 are new and distinct
            a.append(next_new)
            next_new += 1
        else:
            # Some previous element was reused; use the same value as at index (i - diff)
            a.append(a[i - diff])
    return " ".join(map(str, a))


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        print(solve())


# https://github.com/VaHiX/CodeForces/