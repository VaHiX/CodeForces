# Contest 2124, Problem E: Make it Zero
# URL: https://codeforces.com/contest/2124/problem/E

import sys
input = sys.stdin.readline

out = []
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))

    tot = sum(a)
    if tot % 2 or 2 * max(a) > tot:
        out.append('-1')
        continue

    i = 0
    left = 0
    while 2 * (left + a[i]) <= tot:
        left += a[i]
        i += 1

    if 2 * left == tot:
        out.append('1')
        out.append(' '.join(map(str, a)))
        continue

    b = [0] * n
    b[i] = (tot - left - left) // 2
    rem = b[i]
    for j in range(i + 1, n):
        z = min(rem, a[j])
        b[j] = z
        rem -= z
    assert rem == 0
    
    for j in range(n):
        a[j] -= b[j]

    assert min(a) >= 0
    assert min(b) >= 0

    assert sum(a[:i]) == sum(a[i:])

    out.append('2')
    out.append(' '.join(map(str, a)))
    out.append(' '.join(map(str, b)))

print('\n'.join(out))
