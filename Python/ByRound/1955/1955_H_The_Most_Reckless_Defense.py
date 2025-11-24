# Problem: CF 1955 H - The Most Reckless Defense
# https://codeforces.com/contest/1955/problem/H

"""
Code Purpose:
This code solves the "The Most Reckless Defense" problem, which involves
optimizing tower ranges in a Tower Defense game to maximize the base health
of enemies that can pass through a path without dying. Each tower can have
a range from 1 to 10, and when set, it increases enemy health by 3^r, but each
r can only be used once. The goal is to determine the maximum base health h
such that the player still wins with this configuration.

Algorithms/Techniques:
- Dynamic Programming with Bitmasking
- Preprocessing tower coverage for different ranges
- Optimization to find best combination of tower ranges

Time Complexity: O(N * M * K * 10 + 2^10 * 10)
Space Complexity: O(N * M * K + 2^10)
"""

for _ in range(int(input())):
    N, M, K = map(int, input().split())
    Map = [list(input()) for _ in range(N)]

    A = []
    Dir = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    for _ in range(K):
        a, b, c = map(int, input().split())
        B = [0] * 11
        a -= 1
        b -= 1

        # Precompute for each range how many cells in the path are covered
        for i in range(N):
            for j in range(M):
                if Map[i][j] == ".":
                    continue
                for k in range(11):
                    # Check if distance squared <= range squared
                    if (a - i) ** 2 + (b - j) ** 2 <= k**2:
                        B[k] += 1
                        break

        # Accumulate coverage to include all ranges up to current 
        for i in range(2, 11):
            B[i] += B[i - 1]
        # Multiply by tower power for each range
        for i in range(1, 11):
            B[i] *= c

        # Store only the first 10 ranges, starting from range 1
        A.append(B[1:])

    # DP with bitmasking to represent which tower ranges are chosen
    P = [0] * (2**10)

    # Iterate through all towers
    for data in A:
        Q = P.copy()

        # For each existing combination of ranges, try adding a new tower
        for i in range(2**10):
            for j in range(10):
                # Check if range j is not already used
                if i & (1 << j) == 0:
                    # Update the maximum damage for new combination
                    Q[i | (1 << j)] = max(Q[i | (1 << j)], P[i] + data[j])

        P = Q.copy()

    Ans = 0
    # Try all combinations of range assignments
    for i in range(2**10):
        n = i
        cnt = 0
        # Calculate the health increase from chosen ranges
        for j in range(10):
            cnt += (n % 2) * (3 ** (j + 1))
            n //= 2

        # Update answer with max damage minus health increase
        Ans = max(Ans, P[i] - cnt)

    print(Ans)


# https://github.com/VaHiX/CodeForces/