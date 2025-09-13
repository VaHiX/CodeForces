# Contest 2010, Problem C2: Message Transmission Error (hard version)
# URL: https://codeforces.com/contest/2010/problem/C2

s=input()
C=len(s)
f=[0]*C
f[0]=-1
for i in range(1,C):
    f[i]=f[i-1]
    while f[i]>=0 and s[f[i]+1]!=s[i]:
        f[i]=f[f[i]]
    if(s[f[i]+1]==s[i]):
        f[i]=f[i]+1
if (f[C-1]+1)*2>C:
    print("YES\n"+s[0:f[C-1]+1])
else:
    print("NO")