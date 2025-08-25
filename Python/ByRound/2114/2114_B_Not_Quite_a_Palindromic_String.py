# Contest 2114, Problem B: Not Quite a Palindromic String
# URL: https://codeforces.com/contest/2114/problem/B

baku = []
for _ in range(int(input())):
    n, k = [int(t) for t in input().split()]
    c = input().count("0")
    m = n // 2 - min(c, n - c)
    baku.append("YES" if m <= k and (m - k) % 2 == 0 else "NO")
print(*baku)
