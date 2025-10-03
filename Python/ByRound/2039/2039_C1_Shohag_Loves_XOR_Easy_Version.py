# Contest 2039, Problem C1: Shohag Loves XOR (Easy Version)
# URL: https://codeforces.com/contest/2039/problem/C1

for _ in range(int(input())):
    x, m = map(int, input().split())
    t = 0
    for i in range(1, x):
        y = x ^ i
        if y > m:
            continue
        if y % (x ^ y) == 0 or x % (x ^ y) == 0:
            t += 1
    print(t)
