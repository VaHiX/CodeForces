# Contest 2008, Problem G: Sakurako's Task
# URL: https://codeforces.com/contest/2008/problem/G

import io, sys
import math
input = lambda: sys.stdin.readline().strip()
kase = int(input())
outs = []
for _ in range(kase):
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))
    if n == 1:
        if k <= nums[0]: outs.append(k-1)
        else: outs.append(k)
    else:
        d = math.gcd(*nums)
        if k > (n-1)*(d-1):
            outs.append(n+k-1)
        else:
            x, rare = divmod(k-1, d-1)
            outs.append(d*x + rare + 1)

print('\n'.join(map(str, outs)))