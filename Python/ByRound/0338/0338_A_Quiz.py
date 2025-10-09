# Contest 338, Problem A: Quiz
# URL: https://codeforces.com/contest/338/problem/A

n, m, k = map(int, input().split())
# k continuos chahiye
# n number of questions hai
# m correctly answer kiya hai
mod = 10**9 + 9
gaps = m - ((n // k) * (k - 1) + n % k)
if gaps <= 0:
    exit(print(m % mod))
# print(gaps)
ans1 = m - gaps
ans2 = (pow(2, gaps + 1, mod) - 2 + 2 * mod) * k
ans3 = -gaps * (k - 1)
print((ans1 + ans2 + ans3) % mod)
