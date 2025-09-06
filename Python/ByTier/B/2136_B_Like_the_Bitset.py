# Contest 2136, Problem B: Like the Bitset
# URL: https://codeforces.com/contest/2136/problem/B

import sys
input = sys.stdin.readline
for t in range(int(input())):
    n,k = map(int,input().split())
    s=input().strip()
    if '1'*k in s: 
        print("NO")
        continue
    print("YES")
    bpmn = [0]*n
    x = n
    for i,ch in enumerate(s):
        if ch == '0': 
            bpmn[i] = x
            x -= 1
    for i,ch in enumerate(s):
        if ch == '1': 
            bpmn[i] = x
            x -= 1
    print(*bpmn)