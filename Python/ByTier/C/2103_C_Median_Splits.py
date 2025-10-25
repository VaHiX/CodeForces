# Problem: CF 2103 C - Median Splits
# https://codeforces.com/contest/2103/problem/C

# C. Median Splits
# Algorithm: Greedy + Prefix Sum
# Time Complexity: O(n) per test case
# Space Complexity: O(n) per test case
#
# The problem asks whether an array can be split into three contiguous subarrays
# such that the median of their medians is at most k.
#
# Approach:
# 1. For each valid split (l, r), compute the median of subarrays [0,l], [l+1,r], [r+1,n-1].
# 2. Since we only care about existence, we can use a greedy-like approach with prefix sums
#    to determine if such a partition exists.
# 3. Prefix sum array helps in tracking how many elements are <= k at any position.
# 4. By analyzing the behavior of this prefix sum and maintaining min/max values,
#    we check whether there's a valid split that satisfies the constraint.

import sys as s

I = s.stdin.read


def O():
    D = I().split()
    X = 0
    T = int(D[X])
    X += 1
    for _ in range(T):
        N = int(D[X])
        K = int(D[X + 1])
        X += 2
        A = list(map(int, D[X : X + N]))
        X += N
        # Build prefix sum array where each element is +1 if A[i] <= k else -1
        P = [0] * (N + 1)
        for i in range(1, N + 1):
            P[i] = P[i - 1] + (1 if A[i - 1] <= K else -1)
        T0 = P[N]  # Total imbalance from all elements
        M1 = P[1]  # Minimum prefix value seen so far from left
        M2 = P[1] if P[1] >= 0 else 1 << 60  # Smallest non-negative prefix
        G = P[1] >= 0  # Flag indicating whether we've seen a non-negative prefix sum yet
        F = 0  # Flag to indicate if valid split is found
        for R in range(2, N):  # Iterate over possible right boundary of middle subarray
            Q = P[R]
            # If all conditions are met to satisfy valid median split
            if G and M2 <= Q:
                F = 1
                break
            if G and Q <= T0:
                F = 1
                break
            if M1 <= Q and Q <= T0:
                F = 1
                break
            # Update min prefix sum seen so far
            if Q < M1:
                M1 = Q
            # If current prefix is >= 0, update the minimum non-negative value
            if Q >= 0:
                if not G or Q < M2:
                    M2 = Q
                G = 1  # Set flag since we've seen a non-negative prefix
        print("YES" if F else "NO")


O()


# https://github.com/VaHiX/codeForces/