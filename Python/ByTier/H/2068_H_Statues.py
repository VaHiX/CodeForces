# Contest 2068, Problem H: Statues
# URL: https://codeforces.com/contest/2068/problem/H

import sys

inp = lambda: sys.stdin.readline().rstrip()
Inp = lambda: [*map(int, sys.stdin.readline().split())]


(n,) = Inp()
x, y = Inp()
A = Inp()


X = [(0, 0)]
for a in A:
    x1, x2 = X[-1]
    y2 = x2 + a
    if x1 - a <= 0 <= x2 - a:
        y1 = (x2 - a) % 2
    else:
        y1 = min(abs(x2 - a), abs(x1 - a))
    X.append((min(y1, y2), max(y1, y2)))

x1, x2 = X[-1]
if not (x1 <= abs(x) + abs(y) <= x2 and (x + y) % 2 == x1 % 2):
    print("NO")
else:
    print("YES")
    Ans = [(x, y)]
    p = abs(x) + abs(y)
    for i, (p1, p2) in enumerate(X[:-1][::-1]):
        a = A[~i]
        q2 = p + a
        q1 = abs(p - a)
        q = min(p2, max(q1, q2))

        # for d in range(a+1):
        #     x1, y1 = x-a+d, y-d
        #     if abs(x1)+abs(y1) == q:
        #         x, y = x1, y1
        #         break
        # else:
        #     for d in range(a+1):
        #         x1, y1 = x+a-d, y-d
        #         if abs(x1)+abs(y1) == q:
        #             x, y = x1, y1
        #             break
        #     else:
        #         for d in range(a+1):
        #             x1, y1 = x+a-d, y+d
        #             if abs(x1)+abs(y1) == q:
        #                 x, y = x1, y1
        #                 break
        #         else:
        #             for d in range(a+1):
        #                 x1, y1 = x-a+d, y+d
        #                 if abs(x1)+abs(y1) == q:
        #                     x, y = x1, y1
        #                     break

        for b1, c1 in (-1, q), (1, -q), (1, q), (-1, -q):
            for b2, c2 in (
                (-1, x + a + y),
                (1, -x - a + y),
                (1, -x + a + y),
                (-1, x - a + y),
            ):
                if b1 == b2:
                    if c1 == c2:
                        (x1, y1) = (x, y)
                    else:
                        continue
                else:
                    if b1 == 1:
                        x1 = (c2 - c1) // 2
                        y1 = x1 + c1
                    else:
                        x1 = (c1 - c2) // 2
                        y1 = x1 + c2
                if abs(x1) + abs(y1) == q and abs(x1 - x) + abs(y1 - y) == a:
                    x, y = x1, y1
                    break
            else:
                continue
            break
        else:
            raise
        p = q
        Ans.append((x, y))

    for x, y in Ans[::-1]:
        print(x, y)
