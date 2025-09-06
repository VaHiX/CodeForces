# Contest 872, Problem A: Search for Pretty Integers
# URL: https://codeforces.com/contest/872/problem/A

import sys;sc = sys.stdin.readline;out=sys.stdout.write
n,x=map(int,sc().rstrip().split())
arr=list(map(int,sc().rstrip().split()))
arr1=list(map(int,sc().rstrip().split()))
a=min(arr);aa=min(arr1);s=str(a)+""+str(aa);ss=str(aa)+""+str(a);sss=min(int(s),int(ss));m=[0]*10;o=100000
for e in range(n):m[arr[e]]+=1
for e in range(x):m[arr1[e]]+=1
for e in range(10):
    if m[e]>1:o=e;break
out(str(min(o,sss)))