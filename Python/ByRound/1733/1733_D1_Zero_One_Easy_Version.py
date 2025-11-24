# Problem: CF 1733 D1 - Zero-One (Easy Version)
# https://codeforces.com/contest/1733/problem/D1

"""
Algorithm: Greedy + Observation
Purpose: To find the minimum cost to convert string `a` to string `b` using allowed operations.
Time Complexity: O(n) per test case, where n is the length of the strings.
Space Complexity: O(n) for storing the indices of differing positions.

The approach:
- Identify all positions where the strings differ.
- If the number of differences is odd, it's impossible to make them equal (since each operation flips two bits).
- If there are exactly 2 differences and they are adjacent, choose between using one operation of cost X or two operations of cost Y.
- Otherwise, we can always pair up differences and use operations of cost Y.
"""

Q = int(input())
for i in range(Q):
    N, X, Y = map(int, input().split())
    d = 0
    U = []
    S = input()
    T = input()
    for i in range(N):
        if S[i] != T[i]:
            U.append(i)
            d += 1
    if d % 2 == 1:
        print(-1)
    elif d == 2 and abs(U[0] - U[1]) == 1:
        print(min(X, 2 * Y))
    else:
        print((d // 2) * Y)


# https://github.com/VaHiX/CodeForces/