# Contest 594, Problem A: Warrior and Archer
# URL: https://codeforces.com/contest/594/problem/A

n = int(input())
l = list(map(int, input().split()))
ans = 10**10
n //= 2
l.sort()
for i in range(n):
    ans = min(ans, l[i + n] - l[i])
print(ans)
