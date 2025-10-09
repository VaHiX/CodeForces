n, c1, c2 = map(int, input().split())
s = input().strip()
A = s.count("1")

best = float("inf")

for k in range(1, A + 1):
    extra = n - k
    base = extra // k
    r = extra % k
    cost = k * c1 + c2 * (r * (base + 1) ** 2 + (k - r) * base**2)
    if cost < best:
        best = cost

print(best)
