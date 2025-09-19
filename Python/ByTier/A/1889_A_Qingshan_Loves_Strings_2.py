# Contest 1889, Problem A: Qingshan Loves Strings 2
# URL: https://codeforces.com/contest/1889/problem/A

from collections import deque

for _ in range(int(input())):
    n = int(input())
    s = input()

    if s.count("0") != s.count("1"):
        print(-1)
        continue

    q = deque(s)
    front = 0
    rear = n
    ans = []
    while q:
        if q[0] != q[-1]:
            q.pop()
            q.popleft()
            rear -= 2
        elif q[0] == "1":
            q.appendleft("1")
            q.pop()
            ans.append(front)
        else:
            q.append("0")
            q.popleft()
            ans.append(rear)
        front += 1
        rear += 1

    print(len(ans))
    print(*ans)
