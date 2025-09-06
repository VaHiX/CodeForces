# Contest 780, Problem A: Andryusha and Socks
# URL: https://codeforces.com/contest/780/problem/A

n = int(input())
k = [int(i) for i in input().split()]
p = [0] * n
c = 0
mx = 0
for i in range(2*n):
    if p[k[i]-1] == 0:
        c += 1
        p[k[i] - 1] = 1
    else:
        mx = max(c, mx)
        c -= 1
mx = max(c, mx)
print(mx)