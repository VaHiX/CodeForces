# Contest 2103, Problem C: Median Splits
# URL: https://codeforces.com/contest/2103/problem/C

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
        P = [0] * (N + 1)
        for i in range(1, N + 1):
            P[i] = P[i - 1] + (1 if A[i - 1] <= K else -1)
        T0 = P[N]
        M1 = P[1]
        M2 = P[1] if P[1] >= 0 else 1 << 60
        G = P[1] >= 0
        F = 0
        for R in range(2, N):
            Q = P[R]
            if G and M2 <= Q:
                F = 1
                break
            if G and Q <= T0:
                F = 1
                break
            if M1 <= Q and Q <= T0:
                F = 1
                break
            if Q < M1:
                M1 = Q
            if Q >= 0:
                if not G or Q < M2:
                    M2 = Q
                G = 1
        print("YES" if F else "NO")


O()
