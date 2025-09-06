# Contest 2041, Problem B: Bowling Frame
# URL: https://codeforces.com/contest/2041/problem/B

for _ in range(int(input())): print(int(((1+8*(sum(map(int, input().split()))))**0.5-1)/2))