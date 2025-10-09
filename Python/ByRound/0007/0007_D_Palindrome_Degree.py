# Contest 7, Problem D: Palindrome Degree
# URL: https://codeforces.com/contest/7/problem/D

################################################################################
ss = input()

# ss='abacaba'

# ss='CCeCeCCCee'
################################################################################
n = len(ss)
dp = [0 for i in range(n)]
dp[0] = 1

factor = 123
factor_now = 1
M = 1000000007

prefix = reprefix = ord(ss[0])
for i in range(1, n):
    prefix = (prefix * factor + ord(ss[i])) % M
    factor_now = (factor_now * factor) % M
    reprefix = (reprefix + ord(ss[i]) * factor_now) % M
    if prefix == reprefix:
        dp[i] = dp[(i - 1) // 2] + 1

print(sum(dp))
