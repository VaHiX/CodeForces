# Problem: CF 1906 E - Merge Not Sort
# https://codeforces.com/contest/1906/problem/E

"""
Algorithm: Merge Not Sort
Purpose: Given a permutation C of 1 to 2*N, construct two arrays A and B of length N such that Merge(A,B) = C.
         If impossible, return -1.

Approach:
    - Analyze the pattern of the array C to deduce how it can be split into two subsequences.
    - Use dynamic programming to determine if it's possible to partition the array into segments of sizes
      corresponding to lengths of sorted subsequences.
    - Reconstruct the arrays A and B by following the segment assignment logic.

Time Complexity: O(N^2)
Space Complexity: O(N)

Techniques:
    - Dynamic Programming
    - Greedy segment assignment
"""

import sys

input = sys.stdin.readline
MOD = 10**9 + 7


def read_array(factory):
    return [factory(num) for num in input().strip().split()]


def print_array(arr):
    print(" ".join(map(str, arr)))


def solve(C, n):
    # Find lengths of segments that are increasing
    lengths = []
    curr = C[0]
    length = 1
    for i in range(1, len(C)):
        if C[i] > curr:
            lengths.append(length)
            curr = C[i]
            length = 1
        else:
            length += 1

    lengths.append(length)

    # Dynamic programming to check if we can partition the array
    dp = [False] * (n + 1)
    dp[0] = True
    for l in lengths:
        for i in range(n, l - 1, -1):
            if dp[i - l]:
                dp[i] = True

    if not dp[-1]:
        return ([], [])

    # Reconstruct the order of segments assignment
    order_of_segs = []
    i = n
    while i > 0:
        # Backtrack to find which segments were assigned
        for j in range(i, -1, -1):
            if dp[j] and dp[i] and i - j in lengths:
                order_of_segs.append(i - j)
                i = j
                break

    # Reverse for proper processing
    lengths.reverse()

    A = []
    B = []
    i = 0
    while i < len(C):
        # Assign segment to A if needed
        if order_of_segs and order_of_segs[-1] == lengths[-1]:
            j = order_of_segs[-1]
            for k in range(j):
                A.append(C[i + k])
            i += j
            order_of_segs.pop()
        else:
            # Otherwise assign to B
            j = lengths[-1]
            for k in range(j):
                B.append(C[i + k])
            i += j
        lengths.pop()

    return (A, B)


if __name__ == "__main__":

    n = int(input())
    C = read_array(int)

    A, B = solve(C, n)
    if not A:
        print(-1)
    else:
        print_array(A)
        print_array(B)


# https://github.com/VaHiX/CodeForces/