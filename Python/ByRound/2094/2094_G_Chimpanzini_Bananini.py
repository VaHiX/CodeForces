# Contest 2094, Problem G: Chimpanzini Bananini
# URL: https://codeforces.com/contest/2094/problem/G

import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()
p = []
for _ in range(int(input())):
    arr, ans, s, flag = deque([]), 0, 0, True
    for __ in range(int(input())):
        match input().split():
            case "1",:
                if flag:
                    arr.appendleft(x := arr.pop())
                else:
                    arr.append(x := arr.popleft())
                ans += s - x * len(arr)
            case "2",:
                ans = (len(arr) + 1) * s - ans
                flag = not flag
            case "3", x:
                if flag:
                    arr.append(x := int(x))
                else:
                    arr.appendleft(x := int(x))
                ans += x * len(arr)
                s += x
        p.append(str(ans))
print("\n".join(p))
