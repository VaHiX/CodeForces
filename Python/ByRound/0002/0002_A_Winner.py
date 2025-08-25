# Contest 2, Problem A: Winner
# URL: https://codeforces.com/contest/2/problem/A

n, p, q = int(input()), [], {}
for i in range(n):
    a, b = input().split()
    q[a] = q.get(a, 0) + int(b)
    p.append([a, q[a]])
m = max(q.values())
for i, j in p:
    if q[i] == m and int(j) >= m:
        print(i)
        break
