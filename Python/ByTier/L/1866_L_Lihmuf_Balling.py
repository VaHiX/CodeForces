# Problem: CF 1866 L - Lihmuf Balling
# https://codeforces.com/contest/1866/problem/L

from math import gcd

N, M = map(int, input().split())
ans, bestK = 0, 1
for K in range(2, min(N, M) + 1):
    if N % K == 0:
        # If N is divisible by K, then the pattern repeats every N/K steps
        x = N // K
        # Sum of arithmetic sequence from 1 to x, multiplied by K times
        cur = K * x * (x + 1) // 2
        if cur > ans:
            ans, bestK = cur, K
        continue
    elif gcd(N, K) > 1:
        # If N and K share a common factor, the sequence will have repeated elements
        # which leads to less optimal results, so we skip such K
        continue
    # For general case where N and K are coprime
    cur = 0
    id, c = 1, K
    # Simulate the process of Lihmuf choosing boxes
    while id < N:
        # Compute how many steps we can take in this cycle
        ct = (N - c) // K
        # Compute how many boxes are skipped in this step
        sw = (1 + (id - c) // (K - 1)) if id >= c else 0
        if sw <= ct:
            # Add contribution of balls collected
            cur += c * (ct - sw + 1) + K * (ct * (ct + 1) // 2 - sw * (sw - 1) // 2)
        # Move to next cycle
        id += ct + 1
        # Compute the next starting position of Lihmuf's choice
        c = (c + (ct + 1) * K - 1) % N
        c += 1
    if cur > ans:
        ans, bestK = cur, K
print(bestK)

# https://github.com/VaHiX/CodeForces/