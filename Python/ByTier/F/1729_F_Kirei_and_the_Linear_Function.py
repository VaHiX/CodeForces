# Problem: CF 1729 F - Kirei and the Linear Function
# https://codeforces.com/contest/1729/problem/F

"""
Algorithm: Dynamic Programming with Modular Arithmetic
Approach:
- Precompute prefix sums modulo 9 for efficient substring modulo calculation
- For each possible remainder (0-8), store the first two indices of substrings with that remainder
- For each query, calculate the required remainder of the query substring
- Find valid pairs of substrings that satisfy the equation: (L1 * v_query + L2) % 9 == k
- Use stored indices to quickly find valid pairs

Time Complexity: O(n + m)
Space Complexity: O(n)

Where n is the length of string s and m is the number of queries.
"""

for _ in range(int(input())):
    s = list(map(int, input()))
    w, q = map(int, input().split())
    n = len(s)
    # Precompute prefix sums modulo 9 for quick substring modulo calculation
    pre = [0]
    for x in s:
        pre += [(x + pre[-1]) % 9]

    # Store first two indices for each possible remainder (0-8)
    ind = [[] for _ in range(9)]
    for i in range(n - w + 1):
        x = (pre[i + w] - pre[i] + 9) % 9  # Calculate substring remainder
        if len(ind[x]) == 2:
            continue  # Only keep first two indices for efficiency
        ind[x] += [i + 1]  # Store 1-based index

    for _ in range(q):
        l, r, k = map(int, input().split())
        # Calculate remainder of query substring
        x = (pre[r] - pre[l - 1] + 9) % 9
        ans = [n, n]  # Initialize with large values

        # Check all possible remainders for valid pairs
        for i in range(9):
            if not ind[i]:
                continue
            # Calculate required remainder for second substring
            j = (k - i * x + 9) % 9
            if i == j:
                # Same remainder: need two different substrings
                if len(ind[i]) != 2:
                    continue
                ans = min(ans, ind[i])
            else:
                # Different remainders: find first occurrence of both
                if not ind[j]:
                    continue
                ans = min(ans, [ind[i][0], ind[j][0]])

        if ans == [n, n]:
            print(-1, -1)
        else:
            print(*ans)


# https://github.com/VaHiX/CodeForces/