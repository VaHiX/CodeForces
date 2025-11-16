# Problem: CF 2156 F1 - Strange Operation (Easy Version)
# https://codeforces.com/contest/2156/problem/F1

"""
Problem: Given a permutation of integers from 1 to n, we can perform operations where we select three positions i < j < k such that:
- p[i] = ps + 2
- p[j] = ps
- p[k] = ps + 1

And then update:
- p[i] = p[i] - 2
- p[j] = p[j] + 1
- p[k] = p[k] + 1

The goal is to minimize the lexicographically smaller permutation possible through these operations.
"""

for i in range(int(input())):
    n = int(input())
    p = [0] + list(map(int, input().split()))  # 1-indexed
    pos = [0] * (n + 1)  # position of each value
    for i in range(1, n + 1):
        pos[p[i]] = i

    ps = 1
    ct = 0

    # Main optimization loop
    while ps <= n - 2:
        # Check if we can perform the operation with ps
        if not (
            1 <= ps <= n - 2 and pos[ps + 2] < pos[ps] and pos[ps + 2] < pos[ps + 1]
        ):
            ps += 1
            continue

        # Get positions of elements ps+2, ps, ps+1
        i = pos[ps + 2]
        j = pos[ps]
        k = pos[ps + 1]
        
        # Ensure j <= k
        if j > k:
            j, k = k, j

        # Perform the operations
        p[i] -= 2
        p[j] += 1
        p[k] += 1
        ct += 1

        # Update positions
        pos[p[i]] = i
        pos[p[j]] = j
        pos[p[k]] = k

        # Backtrack a bit for potential further optimizations
        ps = max(ps - 2, 1)

    print(" ".join(map(str, p[1:])))


# https://github.com/VaHiX/CodeForces/