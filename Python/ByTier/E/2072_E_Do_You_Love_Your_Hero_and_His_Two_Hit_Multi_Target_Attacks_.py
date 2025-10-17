# Contest 2072, Problem E: Do You Love Your Hero and His Two-Hit Multi-Target Attacks?
# URL: https://codeforces.com/contest/2072/problem/E

t = int(input())
for _ in range(t):
    k = int(input())
    if not k:
        print(1)
        print("0 0")
        continue
    g = []
    while k:
        m = 2
        while m * (m - 1) // 2 <= k:
            m += 1
        m -= 1
        g += [m]
        k -= m * (m - 1) // 2
    c = [(i * 10000 + j, i) for i, m in enumerate(g) for j in range(m)]
    print(len(c))
    print("\n".join(f"{x} {y}" for x, y in c))
