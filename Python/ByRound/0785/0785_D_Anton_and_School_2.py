# Contest 785, Problem D: Anton and School - 2
# URL: https://codeforces.com/contest/785/problem/D

R = 2 * 10**5
M = 10**9 + 7
F = [1] * (R + 1)
for i in range(1, R + 1):
    F[i] = (F[i - 1] * i) % M
Fhyp = [1] * (R + 1)
Fhyp[R] = pow(F[R], M - 2, M)
for i in range(R - 1, -1, -1):
    Fhyp[i] = (Fhyp[i + 1] * (i + 1)) % M


def C(n, k):
    if n < 0 or k < 0 or n < k:
        return 0
    return (F[n] * Fhyp[n - k] * Fhyp[k]) % M


s = [e == ")" for e in input()]
n = len(s)
l = [0] * n
l[0] = int(s[0] == 0)
for i in range(1, n):
    l[i] = l[i - 1] + (s[i] == 0)
r = [0] * n
r[-1] = int(s[-1] == 1)
for i in range(n - 2, -1, -1):
    r[i] = r[i + 1] + (s[i] == 1)
S = 0
for i in range(n - 1):
    S += C(l[i] + r[i + 1] - 1, l[i]) * (l[i] > 0 and r[i + 1] > 0 and s[i] == 0)
print(S % M)
