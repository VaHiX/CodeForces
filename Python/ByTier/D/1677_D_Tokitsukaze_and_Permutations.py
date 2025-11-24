# Problem: CF 1677 D - Tokitsukaze and Permutations
# https://codeforces.com/contest/1677/problem/D

"""
Algorithm/Technique:
This problem involves determining the number of permutations that can produce a given "value sequence" v after exactly k bubble sort-like operations. The key insight is to analyze how the value sequence v relates to the final sorted order after k operations, and how many valid permutations can lead to the same result.

The approach uses:
1. Dynamic programming principles to calculate the number of valid permutations based on constraints from v.
2. For each position, we consider how many choices we have, taking into account:
   - If v[i] == 0, we can place k+1 elements at that position (based on valid ranges of elements).
   - If v[i] == -1, it's unknown and contributes (i + k + 1) choices.
   - Constraints from v[i] where it's greater than 0, which implies no valid permutations exist (set to 0).
   - Multiply by factorial terms (i+1) for other parts.

Time Complexity: O(n)
Space Complexity: O(1)
"""

MOD = 998244353

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    v = list(map(int, input().split()))

    out = 1
    # Process first n - k elements
    for i in range(n - k):
        if v[i] == 0:
            # When v[i] is 0, we can choose k+1 valid positions
            out *= k + 1
            out %= MOD
        if v[i] == -1:
            # When v[i] is unknown, we can choose (i + k + 1) valid positions
            out *= i + k + 1
            out %= MOD

    # Process last k elements
    for i in range(k):
        if v[~i] > 0:
            # If any value in the last k elements is greater than 0, it's invalid
            out = 0

        # Multiply by factorial term for valid permutations
        out *= i + 1
        out %= MOD

    print(out)


# https://github.com/VaHiX/CodeForces/