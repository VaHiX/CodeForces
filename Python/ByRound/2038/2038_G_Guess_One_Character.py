# Contest 2038, Problem G: Guess One Character
# URL: https://codeforces.com/contest/2038/problem/G

from sys import stdin
input = lambda: stdin.buffer.readline().decode().strip()


def ask(s):
    print(1, s, flush=True)
    return int(input())


for _ in range(int(input())):
    n = int(input())

    c1 = ask('1')
    c10 = ask('10')
    c11 = ask('11')

    if c10 + c11 == c1:
        print(0, n, 0, flush=True)
    
    else:
        print(0, n, 1, flush=True)

    input()