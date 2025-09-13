# Contest 1600, Problem A: Weights
# URL: https://codeforces.com/contest/1600/problem/A

n = int(input())

A = list(map(int, input().split()))
A.sort()

S = input()
S = [0 if S[i] == "L" else 1 for i in range(n)]

P = [-1] * n
cor = S[-1] + n + 1

a = 0
b = n - 1

for c in range(n - 1, -1, -1):

    if S[c - 1] != S[c]:
        P[b] = c
        b -= 1
    else:
        P[a] = c
        a += 1


Ans = [(P[i], A[i], (i + cor) % 2) for i in range(n)]
Ans.sort()

for ans in Ans:
    print(ans[1], "R" if ans[2] else "L")
