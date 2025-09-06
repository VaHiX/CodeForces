# Contest 2136, Problem F2: From the Unknown (Hard Version)
# URL: https://codeforces.com/contest/2136/problem/F2

import sys
input = sys.stdin.readline

val = {}
for i in range(125, 10 ** 5 + 1):
    cnt = i // 125
    v = 9999 // cnt + 1
    if v not in val:
        val[v] = []
    val[v].append(i)

for _ in range(int(input())):
    q1 = [125 for _ in range(10000)]
    print('?', 10000, *q1, flush = True)
    resp = int(input())
    if resp == 0:
        q2 = [1 for _ in range(15000)]
        print('?', 15000, *q2, flush = True)
        resp2 = int(input())
        for i in range(1, 126):
            if 14999 // i + 1 == resp2:
                print('!', i, flush = True)
                break
    else:
        start, end = val[resp][0], val[resp][-1]
        q2 = []
        length = end - start
        for i in range(1, length + 1):
            q2.append(start)
            q2.append(i)
        print('?', len(q2), *q2, flush = True)
        resp2 = int(input())
        cnt = length * 2
        for i in range(start, end + 1):
            if cnt == resp2:
                print('!', i, flush = True)
                break
            cnt -= 1