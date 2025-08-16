# Contest 2131, Problem G: Wafu!
# URL: https://codeforces.com/contest/2131/problem/G

import sys

input = lambda: sys.stdin.readline().rstrip()
printerr = lambda *args, **kwargs: print("\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs) or (args[0] if len(args) == 1 else args)

MOD = 1000000007

vs = [1, 1]
ps = [1, 1]
ops = [0, 1]
pops = [0, 1]
sz = 2
while ops[-1] <= 1000000000:
    vs.append(sz * ps[-1] % MOD)
    ps.append(ps[-1] * vs[-1] % MOD)
    ops.append(pops[-1] + 1)
    pops.append(pops[-1] + ops[-1])
    sz += 1

def main():
    n, k = map(int, input().split())
    a = sorted(map(int, input().split()))
    ans = 1
    for x in a:
        if x < sz and ops[x] <= k:
            ans = ans * vs[x] % MOD
            k -= ops[x]
            if k == 0: break
        else:
            while k:
                k -= 1
                ans = ans * x % MOD
                x = min(sz - 1, x - 1)
                while pops[x] > k: x -= 1
                k -= pops[x]
                ans = ans * ps[x] % MOD
                x += 1
            break
    print(ans)

tcs = int(input())
for tc in range(tcs):
    main()
