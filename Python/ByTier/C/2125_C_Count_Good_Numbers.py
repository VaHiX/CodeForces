# Contest 2125, Problem C: Count Good Numbers
# URL: https://codeforces.com/contest/2125/problem/C

f=lambda n:n-n//2-n//3-n//5-n//7+n//6+n//10+n//14+n//15+n//21+n//35-n//30-n//42-n//70-n//105+n//210
for s in[*open(0)][1:]:a,b=map(int,s.split());print(f(b)-f(a-1))