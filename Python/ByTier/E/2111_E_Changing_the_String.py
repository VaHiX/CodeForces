# Contest 2111, Problem E: Changing the String
# URL: https://codeforces.com/contest/2111/problem/E

# 12: 15
import sys

input = lambda: sys.stdin.readline().rstrip()
oa = ord("a")


def solve646():
    n, k = map(int, input().split())
    a = [ord(x) - oa for x in input()]
    s20, s12, s21, s10 = [0] * 4
    s120 = s210 = 0
    for i in range(k):
        x, y = input().split()
        x, y = ord(x) - oa, ord(y) - oa
        if x == y or x == 0:
            continue
        if x == 1 and y == 0:
            s10 += 1
            s210 = min(s210 + 1, s21)
        if x == 2 and y == 0:
            s20 += 1
            s120 = min(s120 + 1, s12)
        if x == 2 and y == 1:
            s21 += 1
        if x == 1 and y == 2:
            s12 += 1
    for i, x in enumerate(a):
        if x == 0:
            continue
        if x == 1:
            if s10:
                s10 -= 1
                a[i] = 0
            elif s120 and s20 and s12:
                s120 -= 1
                s20 -= 1
                s12 -= 1
                a[i] = 0
            continue
        # x==2
        if s20:
            s20 -= 1
            a[i] = 0
            continue
        if s21:
            s21 -= 1
            a[i] = 1
            if s210 and s10:
                s10 -= 1
                s210 -= 1
                a[i] = 0
    b = [chr(x + oa) for x in a]
    return "".join(b)


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(res_test))
