# Contest 2122, Problem A: Greedy Grid
# URL: https://codeforces.com/contest/2122/problem/A

for s in[*open(0)][1:]:a,b=sorted(map(int,s.split()));print('YNEOS'[b<3or a<2::2])