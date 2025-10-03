# Contest 1765, Problem N: Number Reduction
# URL: https://codeforces.com/contest/1765/problem/N

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    s = map(int, input())
    k = int(input())

    queue = []
    posqueue = []
    zerocnt = [0]
    for el in s:
        while k > zerocnt[-1] and len(posqueue) > 0 and el < posqueue[-1]:
            if el == 0 and len(posqueue) == 1:
                break
            while queue.pop() == 0:
                k -= 1
            zerocnt.pop()
            posqueue.pop()
            k -= 1
        if el == 0:
            zerocnt[-1] += 1
        else:
            zerocnt.append(0)
            posqueue.append(el)
        queue.append(el)

    sys.stdout.write("".join(map(str, queue[: len(queue) - k])) + "\n")


t = int(input())
for _ in range(t):
    solve()
