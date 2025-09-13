# Contest 2148, Problem A: Sublime Sequence
# URL: https://codeforces.com/contest/2148/problem/A

for _ in range(int(input())):
    x,n=map(int,input().split())
    print(0 if n%2==0 else x)