# Contest 2052, Problem A: Adrenaline Rush
# URL: https://codeforces.com/contest/2052/problem/A

n = int(input())
c = list(map(int, input().split()))
ans = []
for i in range(n):
    for j in range(i + 1, n):
        ans.append(f"{j+1} {i+1}")
s = set()
for i in range(n):
    x = c[i]
    s.add(x)
    for j in range(x + 1, n + 1):
        if j not in s:
            ans.append(f"{x} {j}")
print(len(ans))
print("\n".join(ans))
