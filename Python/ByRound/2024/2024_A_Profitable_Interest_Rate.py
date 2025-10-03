# Contest 2024, Problem A: Profitable Interest Rate
# URL: https://codeforces.com/contest/2024/problem/A

for s in[*open(0)][1:]:j,y=map(int,s.split());print(max(0,j-max(0,y-j)))