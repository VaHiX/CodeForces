# Contest 1089, Problem L: Lazyland
# URL: https://codeforces.com/contest/1089/problem/L

import sys

input = sys.stdin.readline

arr = list(map(int, input().split()))
n, k = arr[0], arr[1]
dict = {}
chosen = list(map(int, input().split()))
unfilledCount = k
convince = list(map(int, input().split()))
spares = []
i = 0
while i < n:
    if chosen[i] not in dict.keys():
        dict[chosen[i]] = convince[i]
        unfilledCount -= 1
    else:
        if dict[chosen[i]] > convince[i]:
            spares.append(convince[i])
        else:
            spares.append(dict[chosen[i]])
            dict[chosen[i]] = convince[i]
    i += 1
if unfilledCount == 0:
    print(0)
else:
    spares.sort()
    print(sum(spares[:unfilledCount]))
