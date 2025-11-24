# Problem: CF 1994 G - Minecraft
# https://codeforces.com/contest/1994/problem/G

"""
Algorithm: Dynamic Programming on Binary Representation
- For each bit position from most significant to least significant, we compute whether it's possible to set x's bit to 0 or 1 such that the XOR sum matches the target s.
- We maintain a DP table where DP[i][j] stores the validity of achieving j (number of 1s in XOR) for the i-th bit. 
- We track the transition with FROM to reconstruct the answer.

Time Complexity: O(n * k)
Space Complexity: O(n * k)

This is a bit-by-bit dynamic programming solution. We process bits from high to low. For each bit position, we count how many elements in A have 1 at that position. Then we try both possibilities (x bit = 0 or 1), and propagate the information to next bit.
"""

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n, k = map(int, input().split())

    S = input().strip()
    A = [input().strip() for i in range(n)]

    if n == 1:
        ANS = []
        for i in range(k):
            if S[i] == A[0][i]:
                ANS.append(0)
            else:
                ANS.append(1)

        print("".join(map(str, ANS)))
        continue

    # DP[i][j] - at bit i, number of set bits in sum so far is j, is it valid
    DP = [[-1] * n for i in range(k + 1)]
    # FROM[i][j] - from which previous state did we transit to current state
    FROM = [[-1] * n for i in range(k + 1)]

    # Initialize base case
    DP[k][0] = 0
    FROM[k][0] = 0

    for i in range(k - 1, -1, -1):
        one = 0
        for j in range(n):
            if A[j][i] == "1":
                one += 1
        zero = n - one

        if S[i] == "1":
            flag = 1
        else:
            flag = 0

        for j in range(n):
            if DP[i + 1][j] == -1:
                continue

            ku = j

            # Try setting x's bit to 1
            if (ku + one) % 2 == flag:
                DP[i][(ku + one) // 2] = 0  # this means we set x's bit to 1 to get 0 in the result
                FROM[i][(ku + one) // 2] = j

            # Try setting x's bit to 0
            if (ku + zero) % 2 == flag:
                DP[i][(ku + zero) // 2] = 1  # this means we set x's bit to 0 to get 1 in the result
                FROM[i][(ku + zero) // 2] = j

    if DP[0][0] == -1:
        print(-1)
    else:
        ANS = []
        ind = 0
        for i in range(k):
            ANS.append(DP[i][ind])
            ind = FROM[i][ind]

        print("".join(map(str, ANS)))


# https://github.com/VaHiX/CodeForces/