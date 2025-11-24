# Problem: CF 2154 C1 - No Cost Too Great (Easy Version)
# https://codeforces.com/contest/2154/problem/C1

"""
Algorithm: 
- Use smallest prime factor (SPF) sieve to precompute prime factors for numbers up to 2*10^5.
- For each number in array 'a', find its prime factors and store them in a set.
- Check if any two numbers in the array already share a prime factor (i.e., gcd > 1).
  - If yes, answer is 0.
- Otherwise, for each number in array 'a', check if incrementing it by 1 results in a number that shares a prime factor with any number in the array.
  - If yes, answer is 1.
- If none of the above conditions are met, answer is 2.

Time Complexity: O(MAXA * log(log(MAXA)) + n * sqrt(MAXA))
Space Complexity: O(MAXA)
"""

import sys

input = sys.stdin.read
data = list(map(int, input().split()))
i = 0
t = data[i]
i += 1
MAXA = 200005
spf = [x for x in range(MAXA)]  # smallest prime factor array
x = 2
while x * x < MAXA:
    if spf[x] == x:  # x is a prime
        y = x * x
        while y < MAXA:
            if spf[y] == y:
                spf[y] = x  # update smallest prime factor
            y += x
    x += 1
res = []
for _ in range(t):
    n = data[i]
    i += 1
    a = data[i : i + n]
    i += n
    i += n  # skip b array which is all 1s
    d = {}
    ok = False
    for v in a:
        s = set()
        x = v
        while x > 1:
            p = spf[x]
            if p not in s:
                if p in d:
                    ok = True
                    break
                d[p] = 1
                s.add(p)
            x //= p
        if ok:
            break
    if ok:
        res.append("0")
        continue
    base = set(d.keys())
    ok = False
    for v in a:
        s = set()
        x = v + 1
        while x > 1:
            p = spf[x]
            if p not in s:
                if p in base:
                    ok = True
                    break
                s.add(p)
            x //= p
        if ok:
            break
    if ok:
        res.append("1")
    else:
        res.append("2")
print("\n".join(res))


# https://github.com/VaHiX/CodeForces/