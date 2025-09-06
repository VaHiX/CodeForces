# Contest 1079, Problem A: Kitchen Utensils
# URL: https://codeforces.com/contest/1079/problem/A


import functools
import sys
# sys.setrecursionlimit(2000000)
from collections import defaultdict
import collections
#from sortedcontainers import SortedList
import math
import heapq
from collections import deque
import bisect
import sys
input = sys.stdin.readline
import itertools
from math import gcd
fmin = lambda x,y: x if x < y else y
fmax = lambda x,y: x if x > y else y


def solve(N,K,arr):
    needed = 0

    #distinct = len(set(arr))
    max_count = collections.Counter()
    for x in arr:
        max_count[x] += 1
    
    #Z = max(max_count.values())

   # ans = 0
    for key,count in max_count.items():
        needed = fmax(needed, ((count + K - 1)//K)*K)
        #print(key,((count + K - 1)//K)*K)
        #ans += Z-count
    #print(needed)
    return needed*len(set(arr)) - len(arr) 




    # print(K,distinct,max_count)

    # return K*distinct*max_count-len(arr)

# t = int(input())
# for j in range(1 , t +1):
#S = input()
#N = int(input())
#A = input().strip()
#mat = []
#A,B = input().split(" ")
N, K = list(map(int,input().strip().split(" ")))
arr = list(map(int,input().strip().split(" ")))

result = solve(N,K,arr)
print(result)
#print("Case #{}: {}".format(j, result))
## print('{:.8f}'.format(result))
