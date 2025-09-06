# Contest 2135, Problem D1: From the Unknown (Easy Version)
# URL: https://codeforces.com/contest/2135/problem/D1

from sys import stdout

m1 = [0] * 100001
m2 = [0] * 100001
for i in range(1, 330):
    m1[99999 // i + 1] = i
for i in range(1, 100000 // 330 + 1):
    m2[99999 // i + 1] = i * 330

def solve():
    global m1, m2
    print('? 100000' + ' 330' * 100000)
    stdout.flush()
    res = int(input())
    if res == 0:
        print('? 100000' + ' 1' * 100000)
        stdout.flush()
        res = int(input())
        print(f'! {m1[res]}')
    else:
        l = m2[res]
        print('? 658 ' + ' '.join([f'{l} {i}' for i in range(1, 330)]))
        stdout.flush()
        res = int(input())
        print(f'! {l + 658 - res}')

for ca in range(int(input())):
    solve()