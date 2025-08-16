# Contest 2118, Problem A: Equal Subsequences
# URL: https://codeforces.com/contest/2118/problem/A

for _ in range(int(input())):
 n,k=map(int,input().split());s='1'*k+'0'*(n - k);print(s)