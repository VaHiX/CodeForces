# Contest 2021, Problem A: Meaning Mean
# URL: https://codeforces.com/contest/2021/problem/A

for s in[*open(0)][2::2]:
 p,*a=sorted(map(int,s.split()))
 for x in a:p=x+p>>1
 print(p)