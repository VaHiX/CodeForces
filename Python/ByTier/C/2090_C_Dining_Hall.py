# Contest 2090, Problem C: Dining Hall
# URL: https://codeforces.com/contest/2090/problem/C

import sys

input = sys.stdin.readline
print = sys.stdout.write
t = int(input())
for _ in range(t):
    n = int(input())
    s = list(map(int, input().split()))[::-1]
    rst = []
    m2 = 2
    m2_c = 0
    m3 = 3
    m3_c = 0
    while s:
        i = s.pop()
        # print(f'{i} {m2} {m3}\n')
        if i == 0 or m2 < m3:
            x = 1 + 3 * m2_c
            y = m2 - x
            rst.append((x, y))
            m2_c += 1
            if m2 + 1 == 3 * m2_c:
                m2 += 3
                m2_c = 0
        else:
            if m3_c % 3 == 0:
                x = 1 + m3_c
                y = m3 - x
            elif m3_c % 3 == 1:
                x = 1 + m3_c
                y = m3 - x - 2
                if m3 == m3_c + 2:
                    y += 2
            elif m3_c % 3 == 2:
                x = m3_c
                y = m3 - x
            rst.append((x, y))
            m3_c += 1
            if m3 == m3_c + 1:
                m3 += 3
                m3_c = 0
    for i in rst:
        print(f"{i[0]} {i[1]}\n")
