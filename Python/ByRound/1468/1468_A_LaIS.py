# Contest 1468, Problem A: LaIS
# URL: https://codeforces.com/contest/1468/problem/A

import bisect as bs
for _ in range(int(input())):
    n, a = int(input()), list(map(int, input().split()))
    stack, m, p = [a[0]], [], [(1000000, 0)]
    for v in a[1:]:
        k = bs.bisect_right(m, v)
        if k == len(m):
            stack.append(v)
            m.append(min(stack[-1], stack[-2]))
        else:
            stack[k + 1] = m[k] = v 
        while p[-1][0] <= v:
            vv, kk = p.pop()
            m[kk] = min(m[kk], vv) 
        if k + 1 < len(m):
            p.append((v, k + 1))
    print(len(stack))