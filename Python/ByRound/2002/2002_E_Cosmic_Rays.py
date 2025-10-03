# Contest 2002, Problem E: Cosmic Rays
# URL: https://codeforces.com/contest/2002/problem/E

#!/usr/local/bin/python3

import sys
input = sys.stdin.readline

def ri(): return int(input())
def rl(v_type=int): return list(map(v_type, input().split()))
def rs(): return input().rstrip()
def out(x, sep=' '): return sep.join(map(str, x))

def solve_case():
    n = ri()
    stk = [] # (color, length)
    res = []
    ans = 0
    for _ in range(n):
        a, b = rl()
        l = 0
        while stk and (a > 0 or stk[-1][0] == b):
            if stk[-1][0] == b:
                l += stk.pop()[1]
            else:
                take = min(a, stk[-1][1])
                a -= take
                l += take
                stk[-1][1] -= take
                if stk[-1][1] == 0:
                    stk.pop()
        ans += a
        l += a
        stk.append([b, l])
        res.append(ans)
    return out(res)


if __name__ == '__main__':
    T = int(input())
    # T = 1
    ret = [solve_case() for ti in range(1, T + 1)]
    print(out(ret, '\n'))
