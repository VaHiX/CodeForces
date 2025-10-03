# Contest 5, Problem C: Longest Regular Bracket Sequence
# URL: https://codeforces.com/contest/5/problem/C

S = input()
N = len(S)
S = ")" + S
dp = [0] * (N + 3)
for i in range(1, N + 1):
    if S[i] == ")" and S[i - dp[i - 1] - 1] == "(":
        dp[i] = dp[i - dp[i - 1] - 2] + dp[i - 1] + 2
mx = max(dp)
if mx:
    print(mx, dp.count(mx))
else:
    print(0, 1)
