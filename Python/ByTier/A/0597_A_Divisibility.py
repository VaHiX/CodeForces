# Contest 597, Problem A: Divisibility
# URL: https://codeforces.com/contest/597/problem/A

a, b, c = map(int, input().split())
b += [(a - abs(b) % a) * (abs(b) % a != 0), abs(b) % a][b < 0]
c -= [(a - abs(c) % a) * (abs(c) % a != 0), abs(c) % a][c > 0]
print((c - b) // a + 1)
