# Contest 951, Problem A: Plasticine zebra
# URL: https://codeforces.com/contest/951/problem/A

s = input()

n = len(s)

cnt, ans = 0, 0
prev = ""
for c in 2 * s:
    cc = "b" if c == "w" else "w"
    cnt = cnt + 1 if cc == prev else 1
    prev = c
    ans = max(ans, min(n, cnt))
print(ans)
