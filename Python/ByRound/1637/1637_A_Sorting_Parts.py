# Contest 1637, Problem A: Sorting Parts
# URL: https://codeforces.com/contest/1637/problem/A

for s in[*open(0)][2::2]:print('YNEOS'[sorted(a:=s.split(),key=int)==a::2])