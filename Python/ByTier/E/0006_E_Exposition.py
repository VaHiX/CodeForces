# Contest 6, Problem E: Exposition
# URL: https://codeforces.com/contest/6/problem/E

from collections import deque

n, k = map(int, input().split())
h = list(map(int, input().split()))

Len = 0
Ans = []
QM = deque()
Qm = deque()

i = 0
j = 0
while i < n:
    while QM and h[QM[-1]] <= h[i]:
        QM.pop()
    QM.append(i)
    while Qm and h[Qm[-1]] >= h[i]:
        Qm.pop()
    Qm.append(i)
    while h[QM[0]] - h[Qm[0]] > k:
        j = min(QM[0], Qm[0]) + 1
        if QM[0] < Qm[0]:
            QM.popleft()
        else:
            Qm.popleft()
    if i - j + 1 > Len:
        Len = i - j + 1
        Ans = [i]
    elif i - j + 1 == Len:
        Ans.append(i)
    i += 1

Cnt = len(Ans)
print(Len, Cnt)
for i in Ans:
    print(i - Len + 2, i + 1)
