# Problem: CF 1806 F2 - GCD Master (hard version)
# https://codeforces.com/contest/1806/problem/F2

"""
Algorithm: Greedy + Prefix Sum + GCD Optimization

Purpose:
This solution computes the maximum possible sum of an array after performing exactly k operations,
where each operation replaces two elements by their GCD. The approach uses greedy selection:
- Sort the array to process smaller elements first
- Precompute prefix sums and GCD-related values
- Try all valid combinations of how many elements to keep as-is vs. how many to reduce via GCD

Time Complexity: O(N log N + N^2), where N is the length of input array
Space Complexity: O(N), due to auxiliary arrays B and C

Key Techniques:
- Sorting for optimal greedy choice
- Prefix sum for quick sum computation
- GCD handling with optimization
"""

from math import gcd

for _ in range(int(input())):
    N, M, K = map(int, input().split())
    A = list(map(int, input().split()))
    su = sum(A)
    A.sort()
    B, C = [0], [0]
    for i in range(1, N):
        if A[i] == A[i - 1]:
            B.append(A[i])
    for i in range(1, len(B)):
        B[i] += B[i - 1]
    A = list(set(A))
    g, s = A[0], A[0]
    for i in range(1, len(A)):
        C.append(s + A[i] - gcd(A[i], g))
        if C[-1] != s + A[i] - g:
            for j in range(i + 1, len(A)):
                C[-1] = min(C[-1], s + A[j] - gcd(g, A[j]))
        g = gcd(g, A[i])
        s += A[i]
    ans = 0
    for i in range(K + 1):
        if len(C) > i and len(B) > K - i:
            ans = max(su - B[K - i] - C[i], ans)
    print(ans)


# https://github.com/VaHiX/CodeForces/