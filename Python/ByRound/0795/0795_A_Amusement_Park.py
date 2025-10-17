# Contest 795, Problem A: Amusement Park
# URL: https://codeforces.com/contest/795/problem/A

n, c1, c2 = map(int, input().split())
s = input().strip()
m = s.count("1")

min_cost = float("inf")

for k in range(1, m + 1):
    total = n - k
    q, r = divmod(total, k)
    sum_sq = q * q * (k - r) + (q + 1) * (q + 1) * r
    cost = k * c1 + c2 * sum_sq
    if cost < min_cost:
        min_cost = cost

print(min_cost)
