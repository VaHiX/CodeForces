# Contest 2025, Problem B: Binomial Coefficients, Kind Of
# URL: https://codeforces.com/contest/2025/problem/B

MOD = 1000000007
t = input()
a = input()
b = [pow(2, int(i), MOD) for i in input().split()]
for i in b:
    print(i)
