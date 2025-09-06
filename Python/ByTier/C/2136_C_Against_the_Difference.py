# Contest 2136, Problem C: Against the Difference
# URL: https://codeforces.com/contest/2136/problem/C

for s in[*open(0)][2::2]:
 a=s.split();c=[i:=0];b=c+[[]for _ in a]
 for x in map(int,a):i+=1;l=b[x];l+=i,;c+=max(c[-1],x<=len(l)and x+c[l[-x]-1]),
 print(c[-1])