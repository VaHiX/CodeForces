# Contest 2037, Problem A: Twice
# URL: https://codeforces.com/contest/2037/problem/A

for s in[*open(0)][2::2]:a=s.split();print(sum(a.count(x)//2for x in{*a}))