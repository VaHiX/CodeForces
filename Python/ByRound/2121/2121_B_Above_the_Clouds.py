# Contest 2121, Problem B: Above the Clouds
# URL: https://codeforces.com/contest/2121/problem/B

for s in[*open(0)][2::2]:print('YNeos'[max(map(s.count,{*s[1:-2]}))<2::2])