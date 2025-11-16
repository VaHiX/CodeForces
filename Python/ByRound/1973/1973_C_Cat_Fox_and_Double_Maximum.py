# Problem: CF 1973 C - Cat, Fox and Double Maximum
# https://codeforces.com/contest/1973/problem/C

"""
Problem: Cat, Fox and Double Maximum

This problem involves finding a permutation q that maximizes the number of local maximums in the array a[i] = p[i] + q[i].

Key insights:
1. A local maximum at index i occurs when a[i-1] < a[i] > a[i+1]
2. To maximize local maximums, we need to strategically place elements in q to create as many such peaks as possible
3. The approach uses sorting and positioning of elements to construct an optimal q

Algorithms/Techniques:
- Greedy construction of permutation q
- Sorting elements and assigning them to positions based on parity
- Using prefix positions to track where each element in p is located

Time Complexity: O(n log n) due to sorting operations
Space Complexity: O(n) for storing arrays and intermediate results
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    P = [int(x) - 1 for x in input().split()]  # Convert to 0-indexed

    pos = [0] * n  # pos[i] = index of element i in permutation P
    for i, p in enumerate(P):
        pos[p] = i

    res = [-1] * n  # Result permutation q
    A = []  # Elements to place in second half (lower values)
    B = []  # Elements to place in first half (higher values)

    # Determine the base case: place the smallest element (0) at an odd index
    if pos[0] % 2:
        res[0] = n // 2 + 1  # Initialize first element of result
        for i in range(1, n):  # Iterate from index 1
            if i % 2:  # Odd indices go to B
                B.append(P[i])
            else:  # Even indices go to A
                A.append(P[i])
    else:
        res[-1] = n // 2 + 1  # Initialize last element of result (even index case)
        for i in range(n - 1):  # Iterate from 0 to n-2
            if i % 2:  # Odd indices go to A
                A.append(P[i])
            else:  # Even indices go to B
                B.append(P[i])

    assert len(A) < len(B)  # Ensure A has fewer elements than B

    # Sort A in descending order and assign to result
    A.sort(reverse=True)
    for i, a in enumerate(A):
        res[pos[a]] = n // 2 + 1 + i + 1  # Place higher indices for A

    # Sort B in descending order and assign to result
    B.sort(reverse=True)
    for i, b in enumerate(B):
        res[pos[b]] = i + 1  # Place lower indices for B

    return " ".join(map(str, res))


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/