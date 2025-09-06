# Contest 1299, Problem A: Anu Has a Function
# URL: https://codeforces.com/contest/1299/problem/A

n = int(input())
x = [int(x) for x in input().strip().split()]

if n == 1:
    print(x[0])
    exit(0)

pref_and = [0] * n
suff_and = [0] * n

for i in range(0, n):
    pref_and[i] = -x[i] - 1
    suff_and[i] = -x[i] - 1

for i in range(1, len(x)):
    pref_and[i] = pref_and[i] & pref_and[i - 1]
    suff_and[len(x) - i - 1] = suff_and[len(x) - i - 1] & suff_and[len(x) - i]

maxim, best = suff_and[1] & x[0], 0
if pref_and[n - 2] & x[n - 1] > maxim:
    maxim = pref_and[n - 2] & x[n - 1]
    best = n - 1

for i in range(1, len(x) - 1):
    if pref_and[i - 1] & suff_and[i + 1] & x[i] > maxim:
        maxim = pref_and[i - 1] & suff_and[i + 1] & x[i]
        best = i

x[0], x[best] = x[best], x[0]
ans = " ".join(str(i) for i in x)

print(ans)