# Contest 1888, Problem A: Chemistry
# URL: https://codeforces.com/contest/1888/problem/A

import sys


def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        n, k = map(int, input().split())
        a = [0] * 26
        for c in input().rstrip():
            a[ord(c) - 97] += 1
        cnt = 0
        for ai in a:
            cnt += ai % 2
        if k < cnt - 1:
            print("NO")
        else:
            print("YES")


main()
