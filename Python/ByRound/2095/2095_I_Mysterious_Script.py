# Contest 2095, Problem I: Mysterious Script
# URL: https://codeforces.com/contest/2095/problem/I

a = ["la", "le", "lon", "sha", "she", "shon", "ta", "te", "ton"]
b = input().split()
c, d = [b[0][:-1], b[1][:-1]]
for i in range(9):
    c, d = c.replace(a[i], str(i)), d.replace(a[i], str(i))
h = int(c, 9) + int(d, 9)
r = ""
while h > 0:
    r = a[h % 9] + r
    h //= 9
print(r + "s")
