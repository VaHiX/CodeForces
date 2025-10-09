# Problem: CF 2048 D - Kevin and Competition Memories
# https://codeforces.com/contest/2048/problem/D

"""
D. Kevin and Competition Memories

Problem Description:
Given n participants with ratings a[i] and m problems with difficulties b[i], we want to compute for each k = 1 to m,
the minimum possible sum of Kevin's ranks across all contests when the problems are distributed optimally into contests
of size k (each contest has exactly k problems, and the last floor(m/k) contests use exactly k problems).

Algorithms/Techniques Used:
- Sorting
- Binary search / Two-pointer technique
- Greedy assignment

Time Complexity: O(n log n + m log m + m^2)
Space Complexity: O(n + m)

The algorithm works as follows:
1. For each k, we consider all possible ways to form contests of size k.
2. We sort the participants' ratings and problem difficulties.
3. For each value of k, we simulate an optimal distribution to minimize Kevin's total rank.
4. For each contest, calculate how many participants solve more than Kevin (using binary search).
5. Sum up these counts for all contests and output the result.

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = sorted(map(int, input().split()))
    q = []
    for i in a:
        if i > a[0]:  # Only consider participants with rating greater than Kevin's (a[0])
            q.append(i)
    q.sort()  # Sort the higher-rated participants
    d = []  # To store rank contributions from each difficulty value
    n_q, j = len(q), 0  # Length of q and pointer for binary search
    for i in b:  # Iterate through sorted problem difficulties
        if i <= a[0]:  # If problem difficulty <= Kevin's rating
            d.append(1)  # Kevin solves this problem (rank contribution is 1)
        else:
            while j < n_q and i > q[j]:  # Move pointer while problem too hard for participant
                j += 1
            d.append(n_q - j + 1)  # Add number of participants who solve more than Kevin
    d.sort()  # Sort rank contributions
    for i in range(1, m + 1):  # For each k from 1 to m
        c = 0  # Accumulator for total rank
        for j in range(i - 1, m, i):  # For every k-th element in d
            c += d[j]
        print(c, end=" ")
    print()


# https://github.com/VaHiX/codeForces/