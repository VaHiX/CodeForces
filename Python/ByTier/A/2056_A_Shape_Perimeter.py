# Contest 2056, Problem A: Shape Perimeter
# URL: https://codeforces.com/contest/2056/problem/A

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    s = 4 * m
    input()
    for i in range(n - 1):
        a, b = map(int, input().split())
        s += 2 * a + 2 * b
    print(s)
