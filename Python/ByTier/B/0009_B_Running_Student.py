# Contest 9, Problem B: Running Student
# URL: https://codeforces.com/contest/9/problem/B

import math

n, vB, vS = map(int, input().split(" "))
ls = list(map(int, input().split(" ")))
x, y = map(int, input().split(" "))
minTime = math.inf
minIndex = 0
curTime = 0
for i in range(1, n):
    curTime += (ls[i] - ls[i - 1]) / vB
    if minTime >= curTime + math.sqrt((x - ls[i]) * (x - ls[i]) + y * y) / vS:
        minIndex = i
        minTime = curTime + math.sqrt((x - ls[i]) * (x - ls[i]) + y * y) / vS
print(minIndex + 1)
