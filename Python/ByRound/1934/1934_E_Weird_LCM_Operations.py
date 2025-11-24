# Problem: CF 1934 E - Weird LCM Operations
# https://codeforces.com/contest/1934/problem/E

"""
Algorithm: Weird LCM Operations
Purpose: Given an integer n, construct an array of n integers where a[i] = i, and perform operations to ensure that all GCDs from 1 to n appear in the set of GCDs of all subsequences with size > 1.

Techniques:
- Precomputed base cases for small n (n <= 14)
- For larger n, use a pattern-based approach to generate operations

Time Complexity: O(n) - Linear in the input size, dominated by the iterative construction for n > 14.
Space Complexity: O(n) - To store the precomputed answers and the operations list for larger inputs.

The algorithm uses a fixed pattern of operations for larger n values, ensuring that all integers from 1 to n can be obtained as GCDs of subsequences.
"""
LANS = [
    [],
    [],
    [],
    [(2, 1, 3)],
    [(3, 4, 1)],
    [(4, 5, 3)],
    [(3, 5, 1), (4, 2, 3), (5, 6, 4)],
    [(6, 1, 5), (7, 3, 4)],
    [(2, 7, 3), (8, 5, 1)],
    [(5, 7, 8), (9, 2, 3)],
    [(4, 10, 2), (2, 4, 1), (3, 5, 8), (3, 9, 7)],
    [(11, 3, 7), (11, 9, 1), (11, 4, 9), (1, 5, 6), (7, 10, 8)],
    [(12, 9, 1), (11, 4, 3), (7, 8, 5)],
    [(5, 11, 2), (3, 7, 13), (4, 8, 1), (2, 6, 9), (2, 10, 5), (4, 12, 7)],
    [(5, 13, 1), (14, 2, 6), (8, 9, 11), (14, 1, 3)],
]


import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n = int(input())

    if n <= 14:
        ANS = LANS[n]

        print(len(ANS))

        for x, y, z in ANS:
            print(x, y, z)
    else:
        ANS = []

        if n % 4 == 3:
            ANS.append((1, 2, n))  # First operation to introduce new values

            k = n - 1  # Start from n-1

            while True:
                if k < n // 2:  # Stop condition to avoid redundant operations
                    break

                s = k - 11  # Starting point of current group of 12 elements
                k -= 12  # Move to next group

                ANS.append((s, s + 1, s + 2))  # First triplet
                ANS.append((s + 4, s + 5, s + 6))  # Second triplet
                ANS.append((s + 8, s + 9, s + 10))  # Third triplet
                ANS.append((s + 3, s + 7, s + 11))  # Fourth triplet

        elif n % 4 == 2:
            k = n  # Start from n

            while True:
                if k < n // 2:  # Stop condition
                    break

                s = k - 11  # Starting point of current group of 12 elements
                k -= 12  # Move to next group

                ANS.append((s, s + 1, s + 2))  # First triplet
                ANS.append((s + 4, s + 5, s + 6))  # Second triplet
                ANS.append((s + 8, s + 9, s + 10))  # Third triplet
                ANS.append((s + 3, s + 7, s + 11))  # Fourth triplet

        elif n % 4 == 1:
            k = n  # Start from n

            while True:
                if k < n // 2:  # Stop condition
                    break

                s = k - 11  # Starting point of current group of 12 elements
                k -= 12  # Move to next group

                ANS.append((s + 1, s + 2, s + 3))  # First triplet (shifted by 1)
                ANS.append((s + 5, s + 6, s + 7))  # Second triplet (shifted by 1)
                ANS.append((s + 9, s + 10, s + 11))  # Third triplet (shifted by 1)
                ANS.append((s, s + 4, s + 8))  # Fourth triplet (shifted by 1)

        else:  # n % 4 == 0
            ANS.append((1, n - 1, n))  # First operation

            k = n - 2  # Start from n-2

            while True:
                if k < n // 2:  # Stop condition
                    break

                s = k - 11  # Starting point of current group of 12 elements
                k -= 12  # Move to next group

                ANS.append((s, s + 1, s + 2))  # First triplet
                ANS.append((s + 4, s + 5, s + 6))  # Second triplet
                ANS.append((s + 8, s + 9, s + 10))  # Third triplet
                ANS.append((s + 3, s + 7, s + 11))  # Fourth triplet

        print(len(ANS))
        for x, y, z in ANS:
            print(x, y, z)


# https://github.com/VaHiX/CodeForces/