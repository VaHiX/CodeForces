# Problem: CF 2172 H - Shuffling Cards with Problem Solver 68!
# https://codeforces.com/contest/2172/problem/H

import sys


def solve():
    """
    Solves the Shuffling Cards problem using an O(n log n) suffix-array-style algorithm
    with counting sort for optimization.

    Time Complexity: O(n log n) where n = 2^k
    Space Complexity: O(n) for storing SA, P, and auxiliary arrays
    """
    k, t_orig = map(int, sys.stdin.readline().split())
    d = sys.stdin.readline().strip()
    n = 1 << k

    if k == 0:
        print(d)
        return

    t_mod_k = t_orig % k
    e = (k - t_mod_k) % k

    def rotl(val, r, num_bits):
        """Cyclic left shift on num_bits-bit integer."""
        if num_bits == 0:
            return 0
        mask = (1 << num_bits) - 1
        return ((val << r) & mask) | (val >> (num_bits - r))

    P = [0] * n
    SA = list(range(n))

    # Initial sort by first character
    SA.sort(key=lambda m: d[m])

    P[SA[0]] = 0
    for i in range(1, n):
        m1, m2 = SA[i - 1], SA[i]
        P[m2] = P[m1] + (d[m1] != d[m2])

    max_rank = P[SA[-1]]

    l = 1
    while l < n:

        shift = rotl(l, e, k)

        # Prepare list of suffixes to sort based on second half
        p_sorted_by_second = [(j - shift + n) % n for j in SA]

        count = [0] * (max_rank + 1)
        for m in p_sorted_by_second:
            count[P[m]] += 1

        # Build prefix sum array for counting sort
        for i in range(1, max_rank + 1):
            count[i] += count[i - 1]

        SA_new = [0] * n
        # Sorting from right to left to maintain stability
        for i in range(n - 1, -1, -1):
            m = p_sorted_by_second[i]
            rank_m = P[m]
            count[rank_m] -= 1
            SA_new[count[rank_m]] = m

        SA = SA_new

        new_P = [0] * n
        for i in range(1, n):
            m1, m2 = SA[i - 1], SA[i]
            pair1 = (P[m1], P[(m1 + shift) % n])
            pair2 = (P[m2], P[(m2 + shift) % n])
            new_P[m2] = new_P[m1] + (pair1 != pair2)

        P = new_P
        max_rank = P[SA[-1]]

        if max_rank == n - 1:
            break

        l *= 2

    best_m = SA[0]

    res_chars = [""] * n
    for p in range(n):
        perm_p = rotl(p, e, k)
        res_chars[p] = d[(best_m + perm_p) % n]

    print("".join(res_chars))


solve()


# https://github.com/VaHiX/CodeForces/