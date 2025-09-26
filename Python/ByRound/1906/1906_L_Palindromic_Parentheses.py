# Contest 1906, Problem L: Palindromic Parentheses
# URL: https://codeforces.com/contest/1906/problem/L

n, k = map(int, input().split())
if k * 2 < n or k == n:
    print("-1")
else:
    print(
        (k - n // 2 + 1) // 2 * "()"
        + "(" * (n - k)
        + ")" * (n - k)
        + (k - n // 2) // 2 * "()"
    )
