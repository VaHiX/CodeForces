# Contest 1, Problem A: Theatre Square
# URL: https://codeforces.com/contest/1/problem/A

n, m, a = map(int, input().split())
print(n // -a * (m // -a))
