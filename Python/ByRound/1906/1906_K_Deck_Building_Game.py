# Problem: CF 1906 K - Deck-Building Game
# https://codeforces.com/contest/1906/problem/K

"""
Algorithm: FFT-like approach for subset sum with XOR convolution
Approach:
- The problem is to count the number of ways to split cards into two decks such that their XOR values are equal.
- This is equivalent to counting pairs of subsets (S1, S2) where XOR(S1) = XOR(S2).
- XOR operation has a property that if XOR(S1) = XOR(S2), then XOR(S1) ^ XOR(S2) = 0.
- This means the XOR of all elements in S1 and S2 combined must be 0.
- We count total number of subsets and use FFT-like transform to compute convolution.
- After transform, for each possible XOR value k, we compute the count of subsets having that XOR and use it to compute result.
Time Complexity: O(M log M) where M = 2^17, so effectively O(17 * 2^17) = O(N)
Space Complexity: O(M) for frequency array and transform array
"""

import sys

mod = 998244353


def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    A = list(map(int, data[1 : 1 + n]))
    M = 1 << 17
    F = [0] * M
    for a in A:
        if a < M:
            F[a] += 1
    h = 1
    while h < M:
        for i in range(0, M, h * 2):
            for j in range(i, i + h):
                x = F[j]
                y = F[j + h]
                F[j] = x + y
                F[j + h] = x - y
        h <<= 1
    base = (mod - 3) % mod
    P = [1] * (n + 1)
    for i in range(1, n + 1):
        P[i] = (P[i - 1] * base) % mod
    sign = 1 if n % 2 == 0 else mod - 1
    total = 0
    for k in range(M):
        n1 = (n + F[k]) // 2
        if n1 < 0 or n1 > n:
            continue
        total = (total + sign * P[n1]) % mod
    invM = pow(M, mod - 2, mod)
    ans = total * invM % mod
    print(ans)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/