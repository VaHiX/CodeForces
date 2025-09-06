# Contest 1242, Problem A: Tile Painting
# URL: https://codeforces.com/contest/1242/problem/A

n = int(input())
if n == 1:
    print(1)
    exit()
p = n
for d in range(2, min(n + 1, int(n ** 0.5) + 2)):
    if n % d == 0:
        p = d
        break
while n % p == 0:
    n //= p
if n != 1:
    print(1)
else:
    print(p)