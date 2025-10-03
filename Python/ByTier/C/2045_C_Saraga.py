# Contest 2045, Problem C: Saraga
# URL: https://codeforces.com/contest/2045/problem/C

S = input()
T = input()
l = len(S) + len(T)
m = "-1"
s = "abcdefghijklmnopqrstuvwxyz"
for h in s:
    i = 1 + S[1:].find(h)
    j = T[:-1].rfind(h)
    if i == 0 or j == -1:
        continue
    new = S[:i] + T[j:]
    k = len(new)
    if k <= l:
        m = new
        l = k
print(m)
