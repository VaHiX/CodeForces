# Contest 22, Problem C: System Administrator
# URL: https://codeforces.com/contest/22/problem/C

from os import path
from sys import stdin, stdout


filename = "../templates/input.txt"
if path.exists(filename):
    stdin = open(filename, "r")


def input():
    return stdin.readline().rstrip()


def print(*args, sep=" ", end="\n"):
    stdout.write(sep.join(map(str, args)))
    stdout.write(end)


def solution():
    n, m, v = [int(num) for num in input().split()]
    if n - 1 <= m <= (n - 1) * (n - 2) // 2 + 1:
        u = v % n + 1
        print(v, u)
        m -= 1
        vs = [i for i in range(1, n + 1) if i != u]
        for i in range(1, len(vs)):
            print(vs[i - 1], vs[i])
            m -= 1
        for i in range(len(vs)):
            for j in range(i + 2, len(vs)):
                if m == 0:
                    break
                print(vs[i], vs[j])
                m -= 1
    else:
        print(-1)


def main():
    t = 1
    while t:
        solution()
        t -= 1


if __name__ == "__main__":
    main()
