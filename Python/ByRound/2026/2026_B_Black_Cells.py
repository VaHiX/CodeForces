# Contest 2026, Problem B: Black Cells
# URL: https://codeforces.com/contest/2026/problem/B


def solve():
    gaps = [1]
    m = 1
    for i in range(1, n, 2):
        m = max(m, a[i] - a[i - 1])
        gaps.append(m)
    if n % 2 == 0:
        return m
    m = 1
    ans = 1e18
    # print(gaps)
    for i in range(n - 1, -1, -2):
        ans = min(ans, max(gaps[i // 2], m))
        # print(ans)
        m = max(m, a[i] - a[i - 1])
    return ans


for t in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(solve())
