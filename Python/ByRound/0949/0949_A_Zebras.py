# Contest 949, Problem A: Zebras
# URL: https://codeforces.com/contest/949/problem/A

import sys
s = sys.stdin.readline().strip()
q = [[], []]
for i, c in enumerate(s):
    k = int(c)
    if not q[1 - k]:
        if k == 1:
            sys.stdout.write('-1')
            sys.exit(0)
        q[k].append([i + 1])
    else:
        q[k].append(q[1 - k].pop())
        q[k][-1].append(i + 1)
if q[1]:
    sys.stdout.write('-1')
else:
    ans = [str(len(q[0]))]
    for it in q[0]:
        ans.append(f'{len(it)} {" ".join(map(str, it))}')
    sys.stdout.write('\n'.join(ans))# 1698153285.4644995