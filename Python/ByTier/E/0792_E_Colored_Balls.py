# Contest 792, Problem E: Colored Balls
# URL: https://codeforces.com/contest/792/problem/E

import math

n = int(input())
s = input().split(" ")
for i in range(len(s)):
    s[i] = int(s[i])
m = min(s)


def try_sz(x):
    for thing in s:
        if thing % x > math.floor(thing / x):
            return False
    return True


good = False
sz = 0
for i in range(1, math.ceil(m**0.5) + 1):
    if try_sz(math.floor(m / i)):
        good = True
        sz = math.floor(m / i)
        break
    if m % i == 0:
        if try_sz(math.floor(m / i) - 1):
            good = True
            sz = math.floor(m / i) - 1
            break
ans = 0
for thing in s:
    ans += math.ceil(thing / (sz + 1))
print(str(ans))
