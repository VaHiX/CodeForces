# Contest 871, Problem A: Maximum splitting
# URL: https://codeforces.com/contest/871/problem/A

for n in[*open(0)][1:]:n=int(n);print(-1if n in[2,5,7,11]else n//4-n%2)