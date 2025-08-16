# Contest 1373, Problem B: 01 Game
# URL: https://codeforces.com/contest/1373/problem/B

for s in[*open(0)][1:]:print('NDEAT'[min(s.count('0'),s.count('1'))%2::2])