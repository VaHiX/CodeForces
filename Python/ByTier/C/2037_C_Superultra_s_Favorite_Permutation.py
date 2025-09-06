# Contest 2037, Problem C: Superultra's Favorite Permutation
# URL: https://codeforces.com/contest/2037/problem/C

for n in[*open(0)][1:]:n=int(n)+1;print(*[[-1],[1,3,*range(7,n,2),5,4,2,*range(6,n,2)]][n>5])