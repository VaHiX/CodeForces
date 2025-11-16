# Problem: CF 1794 C - Scoring Subsequences
# https://codeforces.com/contest/1794/problem/C

"""
Algorithm: Dynamic Programming with Two Pointers
Time Complexity: O(n) amortized per test case
Space Complexity: O(n) for the output array

This solution processes each test case by computing the "cost" of subsequences 
for the prefix [a_1, a_2, ..., a_k] of the given sequence. The cost is defined as  
the maximum length of a subsequence with the maximum possible score.

The key insight is to efficiently track, for each prefix, the maximum length of 
a subsequence that achieves the maximum score. This is done via a two-pointer 
technique where we maintain a value `k` such that we can form a valid subsequence 
of length `k` using elements from the current prefix.

The inner loop uses an amortized analysis: each element is processed at most once 
in the `while` loop across all iterations, leading to a linear time complexity.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

T = int(input())
ans = []
for _ in range(T):
    n = int(input())
    a = list(map(int, input().split()))
    k = 0
    res = []
    for i in range(n):
        # While the condition holds, increment k to find the maximum valid subsequence length
        while k <= i and a[i - k] >= k + 1:
            k += 1
        res.append(k)
    ans.append(" ".join(map(str, res)))

sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/