# Contest 2120, Problem A: Square of Rectangles
# URL: https://codeforces.com/contest/2120/problem/A

for s in[*open(0)][1:]:a=*map(int,s.split()),;(a,b,c),(d,e,f)=sorted((a[::2],a[1::2]));print('YNEOS'[{e,f,a+b+c}!={d}!={e+f,a+b,a+c}::2])