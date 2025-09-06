# Contest 2042, Problem B: Game with Colored Marbles
# URL: https://codeforces.com/contest/2042/problem/B

for s in[*open(0)][2::2]:a=s.split();a=*map(a.count,{*a}),;print(len(a)+a.count(1)%2)