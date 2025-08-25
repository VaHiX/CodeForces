# Contest 2078, Problem E: Finding OR Sum
# URL: https://codeforces.com/contest/2078/problem/E

for _ in range(int(input())):
    M = (1 << 30) - 1
    ns = sum(1 << i for i in range(0, 30, 2))
    nt = sum(1 << i for i in range(1, 30, 2))
    print(ns)
    a = int(input())
    print(nt)
    b = int(input())
    print("!")
    m = int(input())
    s = a + b - 2 * M
    r = s
    for i in range(30):
        if m & (1 << i):
            d = ((a - s) >> i) & 3 if i % 2 == 0 else ((b - s) >> i) & 3
            r += (1 << i) * d
    print(r)
