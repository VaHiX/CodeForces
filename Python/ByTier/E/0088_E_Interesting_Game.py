# Contest 88, Problem E: Interesting Game
# URL: https://codeforces.com/contest/88/problem/E

n=10**5+1
sieve=[[1] for i in range(2*n) ]
for i in range(2,2*n):
    for j in range(i,2*n,i):
        sieve[j].append(i)
prep=[set() for i in range(n)]
prep[1].add((1,1))
for i in range(n):
    for j in sieve[2*i]:
        k=(2*i)//j
        l=(j+k-1)//2
        r=j-l

        if 2*i==((l-r+1)*(l+r)) and l!=r and l>0 and r>0:
            prep[i].add((min(l,r),max(l,r)))

prenim=[0]*(10**5+1)
prefixxor=[0]*(10**5+1)
minimalstat=[10**5+1]*(10**5+1)
for i in range(3,10**5+1):
    e=set()
    for j in prep[i]:
        x,y=j[0],j[1]
        e.add(prefixxor[y]^prefixxor[x-1])
        if prefixxor[y]^prefixxor[x-1]==0 and y-x+1<minimalstat[i]:

            minimalstat[i]=y-x+1
    current=0
    while current in e:
        current+=1
    prenim[i]=current
    prefixxor[i]=prefixxor[i-1]^prenim[i]
n=int(input())
if prenim[n]==0:
    print(-1)
else:
    print(minimalstat[n])
    




















