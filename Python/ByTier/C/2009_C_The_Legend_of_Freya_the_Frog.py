# Contest 2009, Problem C: The Legend of Freya the Frog
# URL: https://codeforces.com/contest/2009/problem/C

for s in[*open(0)][1:]:x,y,k=map(int,s.split());print(-min(-x//k*2+1,-y//k*2))