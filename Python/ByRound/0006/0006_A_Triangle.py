# Contest 6, Problem A: Triangle
# URL: https://codeforces.com/contest/6/problem/A

a, b, c, d = sorted(map(int, input().split()))
x = min(d - b - c, c - a - b)
print(["SEGMENT", "IMPOSSIBLE", "TRIANGLE"][(x > 0) - (x < 0)])
