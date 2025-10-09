# Contest 1047, Problem A: Little C Loves 3 I
# URL: https://codeforces.com/contest/1047/problem/A

n = int(input())
b = 1 + (n % 3 > 1)
print(1, b, n - b - 1)
