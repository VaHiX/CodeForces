# Contest 963, Problem A: Alternating Sum
# URL: https://codeforces.com/contest/963/problem/A

M=10**9+9
n,a,b,k=[int(e) for e in input().split()]
seq=[1 if e=='+' else -1 for e in input()]
s=0
x=pow(a,n,M)
y=(pow(a,-1,M)*b)%M
for i in range(k):
    s+=x*seq[i]
    x*=y
    s%=M
    x%=M
q=pow(y,k,M)
S=s*((n+1)//k)
if q!=1:
    S=s*(pow(q,(n+1)//k,M)-1)*pow(q-1,-1,M)
print(S%M)