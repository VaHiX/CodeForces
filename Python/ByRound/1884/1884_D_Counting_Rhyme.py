# Problem: CF 1884 D - Counting Rhyme
# https://codeforces.com/contest/1884/problem/D

"""
Algorithm: Counting Rhyme
Techniques: 
- Frequency counting with divisor-based processing
- Inclusion-exclusion principle using reverse iteration
- Prefix sum optimization for divisor relationships

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for auxiliary arrays

The problem asks to count pairs (i,j) such that there's no common divisor k such that both a[i] and a[j] are divisible by k.
This is equivalent to saying that gcd(a[i], a[j]) = 1.
We use an approach based on counting frequencies and using inclusion-exclusion to avoid double counting.
"""

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n = int(input())
    A = list(map(int, input().split()))

    # Count frequency of each number
    LIST = [0] * (n + 1)
    for a in A:
        LIST[a] += 1

    ANS = 0

    # SCORE[i] represents the number of pairs where both elements are divisible by i
    SCORE = [0] * (n + 1)

    # For each number i, compute how many pairs have a common divisor i
    for i in range(1, n + 1):
        count = 0
        # Sum up frequencies of all multiples of i
        for j in range(i, n + 1, i):
            count += LIST[j]
        # Number of pairs from count elements = count * (count - 1) / 2
        SCORE[i] = count * (count - 1) // 2

    # USE[i] keeps track of whether we should count pairs involving i
    USE = [0] * (n + 1)

    # Process from large to small to apply inclusion-exclusion
    for i in range(n, 0, -1):
        if SCORE[i] == 0:
            continue
        # Subtract contributions from larger divisors (inclusion-exclusion)
        for j in range(i + i, n + 1, i):
            SCORE[i] -= SCORE[j]

        # Mark all multiples of i as used (they participate in a shared divisor)
        if LIST[i] > 0:
            for j in range(i, n + 1, i):
                USE[j] = 1

    # Final answer is sum of SCORE[i] for i where USE[i] is 0
    ANS = 0
    for i in range(n + 1):
        if USE[i] == 0:
            ANS += SCORE[i]

    print(ANS)


# https://github.com/VaHiX/CodeForces/