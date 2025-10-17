# Contest 1713, Problem F: Lost Array
# URL: https://codeforces.com/contest/1713/problem/F

a = [*map(int, [*open(0)][1].split())]
n = len(a)
for k in 0, 1:
    for i in range(19):
        z = 1 << i
        for j in range(n):
            if j & z:
                a[j - k * z] ^= a[j + k * z - z]
print(*reversed(a))
