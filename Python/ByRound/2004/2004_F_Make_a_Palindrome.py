# Contest 2004, Problem F: Make a Palindrome
# URL: https://codeforces.com/contest/2004/problem/F

import sys
def input():return sys.stdin.readline().rstrip()
out = []
t = int(input())
for _ in range(t):
    n = int(input())
    s = [0] + list(map(int,input().split(' ')))
    for i,c in enumerate(s):
        if i > 0:
            s[i] += s[i-1]
    
    t = []
    for i in range(0,len(s)):
        for j in range(i+1,len(s)):
            t.append(s[i]+s[j])
    
    t.sort()
    save = 0
    cum = 0
    for i in range(len(t)):
        if i>0 and t[i] != t[i-1]:
            cum = 0
        save += cum * 2
        cum += 1
    
    frog = 0
    for i,c in enumerate(t):
        while frog < len(s) and s[frog]*2 < t[i]:
            frog += 1
        if frog < len(s) and s[frog]*2 == t[i]:
            save += 1
    tot = (n-1) * n * (n+1) // 6
    out.append(str(tot - save))
str = '\n'.join(out)
print(str)