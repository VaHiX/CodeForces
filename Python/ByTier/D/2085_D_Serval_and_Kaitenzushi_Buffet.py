# Contest 2085, Problem D: Serval and Kaitenzushi Buffet
# URL: https://codeforces.com/contest/2085/problem/D

import sys

input = sys.stdin.readline
import heapq as hq

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    dcs = [*map(int, input().split())]
    heap = []
    cnt = 0
    for i in range(n - 1, -1, -1):
        cnt += 1
        if cnt == k + 1:
            cnt = 0
            hq.heappush(heap, dcs[i])
        elif heap and heap[0] < dcs[i]:
            hq.heappop(heap)
            hq.heappush(heap, dcs[i])
    print(sum(heap))
