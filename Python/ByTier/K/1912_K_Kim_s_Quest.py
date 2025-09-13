# Contest 1912, Problem K: Kim's Quest
# URL: https://codeforces.com/contest/1912/problem/K

n, a, p110, p101, p011, p000 = int(input()), list(map(int, input().split())), 1, 1, 1, 0
for i in range(n):
    if a[i] % 2 == 0:
        p000, p110 = p000 + 1, (p011 + p110) % 998244353
    else:
        p011, p101 = (p011 + p101) % 998244353, (p110 + p101) % 998244353
print(
    ((p101 + p011 + p110) - 4 - 2 * n - (n * (n - 1)) // 2 + (2**p000) % 998244353)
    % 998244353
)
