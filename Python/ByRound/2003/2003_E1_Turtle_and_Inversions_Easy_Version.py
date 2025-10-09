# Contest 2003, Problem E1: Turtle and Inversions (Easy Version)
# URL: https://codeforces.com/contest/2003/problem/E1

from bisect import bisect,bisect_left

from collections import *
from heapq import *
from math import gcd,ceil,sqrt,floor,inf,pi,lcm,isqrt,log2

from itertools import *
from operator import add,mul,sub,xor,truediv,floordiv
from functools import *

#----------------------------------------------------------------------
import os
import sys

from io import BytesIO, IOBase
# region fastio
 
BUFSIZE = 8192
 
class FastIO(IOBase):
    newlines = 0
 
    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None
 
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()
 
    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()
 
    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)
 
 
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")
 
 
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
 

#------------------------------------------------------------------------
def RL(): return map(int, sys.stdin.readline().split())
def GRL(): return map(lambda x:int(x)-1,sys.stdin.readline().split())
def RLL(): return list(map(int, sys.stdin.readline().split()))
def GRLL(): return list(map(lambda x:int(x)-1,sys.stdin.readline().split()))
def RI():return list(map(int,list(input())))
def N(): return int(input())
def A(n,x=0):return [x]*n
def A2(n,m,x=0): return [[x]*m for i in range(n)]
def A3(a,b,c,x=0):return [[[x]*c for j in range(b)]for _ in range(a)]
def P2(a):
    for r in a:print(*r)
def G(n): return [[] for i in range(n)]
def c2(x):return x*(x-1)//2
def GP(it): return [[ch,len(list(g))] for ch,g in groupby(it)]
def fmax(x,y):return y if y>x else x
def fmin(x,y):return y if y<x else x
def PS(a):return list(accumulate(a,initial=0)) 
#------------------------------------------------------------------------


from types import GeneratorType
 
 
def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to
 
    return wrappedfunc

mod=10**9+7
farr=[1]
ifa=[]
 
def fact(x,mod=0):
    if mod:
        while x>=len(farr):
            farr.append(farr[-1]*len(farr)%mod)
    else:
        while x>=len(farr):
            farr.append(farr[-1]*len(farr))
    return farr[x]
 
def ifact(x,mod):
    global ifa
    fact(x,mod)
    ifa.append(pow(farr[-1],mod-2,mod))
    for i in range(x,0,-1):
        ifa.append(ifa[-1]*i%mod)
    ifa.reverse()
 
def per(i,j,mod=0):
    if i<j: return 0
    if not mod:
        return fact(i)//fact(i-j)
    if i>len(farr):
        res=1
        if j>i-j:j=i-j
        for x in range(i,i-j,-1):
            res=res*x%mod
        return res
    else:
        res=farr[i]
        return res*ifa[i-j]%mod
    
def com(i,j,mod=0):
    if i<j: return 0
    if not mod:        
        return per(i,j)//fact(j)
    if j>i-j:j=i-j
    return per(i,j,mod)*ifa[j]%mod
 
def catalan(n):
    return com(2*n,n)//(n+1)

def matrixmul(a,b,mod):
    return [[sum(x*y for x,y in zip(row,col))%mod for col in zip(*b)]for row in a]

def mpow(n,a,k,mod):
    mul=a
    res=None
    while k:
        if k&1:
            if res==None:
                res=mul
            else:
                res=matrixmul(res,mul,mod)
        k>>=1
        mul=matrixmul(mul,mul,mod)
    return res

def inverse(a,m):
    a%=m
    if a<=1: return a
    return ((1-inverse(m,a)*m)//a)%m

def exgcd(a,b):
    if b==0:
        return 1,0,a
    x,y,g=exgcd(b,a%b)
    x,y=y,(x-a//b*y)
    return x,y,g

def linearbase(a):
    res=[]
    for x in a:
        i=0
        for y in res:
            if x.bit_length()>y.bit_length():break
            if x.bit_length()==y.bit_length():
                x^=y
            i+=1
        if x:
            res.insert(i,x)
    return res

def lowbit(n):
    return n&-n
def GospersHack(k,n):
    cur=(1<<k)-1
    while cur<1<<n:
        yield cur
        lb=cur&-cur
        r=cur+lb
        cur=(r^cur)>>lb.bit_length()+1|r

def modui(ql):
    seq=sorted(range(q),key=lambda x:(ql[x][0]//B,ql[x][1]))
    res=[0]*q
    cnt=[0]*(max(a)+1)
    l,r=ql[seq[0]]
    cur=0
    for i in range(l,r+1):
        cur+=c2(cnt[a[i]])
        cnt[a[i]]+=1
    res[seq[0]]=cur
    #print(seq,ql,res,cnt)
    for i in range(1,q):
        li,ri=ql[seq[i]]
        if ri>r:
            for j in range(r+1,ri+1):
                cur+=c2(cnt[a[j]])
                cnt[a[j]]+=1
        else:
            for j in range(r,ri,-1):
                cnt[a[j]]-=1
                cur-=c2(cnt[a[j]])
        if li>l:
            for j in range(l,li):
                cnt[a[j]]-=1
                cur-=c2(cnt[a[j]])
        else:
            for j in range(l-1,li-1,-1):
                cur+=c2(cnt[a[j]])
                cnt[a[j]]+=1
        res[seq[i]]=cur
        l,r=li,ri
    return res
############################################data structure
class BIT:
    __slots__=('n','arr')
    def __init__(self,n):
        self.n=n 
        self.arr=[0]*n        
    def update(self,x,v):
        while x<self.n:
            self.arr[x]+=v
            x+=x&-x
    def query(self,x):
        ans=0
        while x:
            ans+=self.arr[x]
            x&=x-1
        return ans
    def prod(self,l,r):
        return self.query(r)-self.query(l-1)
    def display(self):
        print([self.query(i) for i in range(1,self.n)])

class SparseTable:
    __slots__=('n','st','e','mx','op')
    def __init__(self,op,e,arr):#n!=0
        n=len(arr)
        mx=n.bit_length()#取不到
        self.op=op
        self.e=e
        self.st=[[0]*mx for i in range(n)]
        for i in range(n):
            self.st[i][0]=arr[i]
        for j in range(1,mx):
            for i in range(n-(1<<j)+1):
                self.st[i][j]=op(self.st[i][j-1],self.st[i+(1<<j-1)][j-1])
    def query(self,l,r):
        if l>r:return self.e
        s=(r+1-l).bit_length()-1
        return self.op(self.st[l][s],self.st[r-(1<<s)+1][s])

class TreeAncestor:
    def __init__(self, n, edges):
        mx=n.bit_length()
        self.par=[[-1]*n for _ in range(mx)]
        g = [[] for _ in range(n)]
        for u,v,w in edges:
            g[u].append((v,w))
            g[v].append((u,w))
        self.dep=[0]*n
        self.cnt=A2(n,27)
        @bootstrap
        def dfs(u,p):
            self.par[u]=p
            for v,w in g[u]:
                if v!=p:
                    cnt[v]=cnt[u].copy()
                    self.dep[v]=dep[u]+1
                    cnt[v][w]+=1
                    yield dfs(v,u)
            yield None
        dfs(0,-1)
        for i in range(mx-1):
            for u in range(n):
                if (p:=self.par[i][u])!=-1:
                    self.par[i+1][u]=self.par[i][p]

    def getKthAncestor(self,node, k):
        for i in range(k.bit_length()):
            if k>>i&1:
                node=self.par[i][node]
                if node<0:break
        return node

    def lca(self,u,v):
        if self.dep[u]<self.dep[v]:
            u,v=v,u
        u=self.getKthAncestor(u,self.dep[u]-self.dep[v])
        if u==v:return u
        for i in range(self.mx-1,-1,-1):
            if self.par[i][u]==self.par[i][v]:continue
            u=self.par[i][u]
            v=self.par[i][v]
        return self.par[0][u]
class DLN:
    def __init__(self,val):
        self.val=val
        self.pre=None
        self.next=None
class Trie:
    def __init__(self):
        self.end=0
        self.children={}
   
class DSU:#容量+路径压缩
    def __init__(self,n):
        self.c=[-1]*n
 
    def same(self,x,y):
        return self.find(x)==self.find(y)
 
    def find(self,x):
        if self.c[x]<0:
            return x
        self.c[x]=self.find(self.c[x])
        return self.c[x]
 
    def union(self,u,v):
        u,v=self.find(u),self.find(v)
        if u==v:
            return False
        if self.c[u]>self.c[v]:
            u,v=v,u
        self.c[u]+=self.c[v]
        self.c[v]=u
        return True
 
    def size(self,x): return -self.c[self.find(x)]
    def groups(self):
        n=len(self.c)
        result= [[] for _ in range(n)]
        for i in range(n):
            result[self.find(i)].append(i)
        return list(filter(lambda r: r, result))

class UF:#秩+路径+容量，边数
    def __init__(self,n):
        self.parent=[i for i in range(n)]
        self.ranks=[0]*n
        self.size=AI(n,1)
        self.edge=A(n)
 
    def find(self,x):
        if x!=self.parent[x]:
            self.parent[x]=self.find(self.parent[x])
        return self.parent[x]
 
    def union(self,u,v):
        pu,pv=self.find(u),self.find(v)
        if pu==pv:
            self.edge[pu]+=1
            return False
        if self.ranks[pu]>=self.ranks[pv]:
            self.parent[pv]=pu
            self.edge[pu]+=self.edge[pv]+1
            self.size[pu]+=self.size[pv]
            if self.ranks[pv]==self.ranks[pu]:
                self.ranks[pu]+=1
        else:
            self.parent[pu]=pv
            self.edge[pv]+=self.edge[pu]+1
            self.size[pv]+=self.size[pu]

#min,non-decreasing stack
def cartesian(a):
    ch=A2(n+1,2)
    stk=[0]
    for i in range(1,n+1):
        while stk and a[stk[-1]]>a[i]:
            stk.pop()
        ch[i][0]=ch[stk[-1]][1]
        ch[stk[-1]][1]=i
        stk.append(i)
    rt=stk[1]
    return rt,ch
############################################################# 
def Prime(n):
    c=0
    prime=[]
    flag=[0]*(n+1) 
    for i in range(2,n+1):
        if not flag[i]:
            prime.append(i)
            c+=1
        for j in range(c):
            if i*prime[j]>n: break
            flag[i*prime[j]]=prime[j]
            if i%prime[j]==0: break
    return flag
 
def rotate(a):#clockwise 90° return tuple
        return list(zip(*reversed(a)))
    
def lis(nums):
    res=[]
    for k in nums:
        i=bisect_left(res,k)
        if i==len(res):
            res.append(k)
        else:
            res[i]=k
    return len(res)

def RP(nums):#逆序对
    n = len(nums)
    s=set(nums)
    d={}
    for i,k in enumerate(sorted(s),1):
        d[k]=i
    bi=BIT([0]*(len(s)+1))
    ans=0
    for i in range(n-1,-1,-1):
        ans+=bi.query(d[nums[i]]-1)
        bi.update(d[nums[i]],1)
    return ans

def michange(a,b):
    d=defaultdict(deque)
    for i,x in enumerate(b):
        d[x].append(i)
    order=A(len(a))
    for i,x in enumerate(a):
        if not d:
            return -1
        order[i]=d[x].popleft()
    return RP(order)


###############################################graph
def nb(i,j,n,m):
    for ni,nj in [[i+1,j],[i-1,j],[i,j-1],[i,j+1]]:
        if 0<=ni<n and 0<=nj<m:
            yield ni,nj
            
def kru(n,e):
    dsu=DSU(n+1)
    e.sort()
    res=0
    cnt=n
    for w,u,v in e:
        if dsu.same(u,v):continue
        dsu.union(u,v)
        res+=w
        cnt-=1
    return res if cnt==1 else inf

def bell(s):#bellman-Ford
    dis=A(n,inf)
    dis[s]=0
    for i in range(n-1):
        for u,v,w in edge:
            if dis[v]>dis[u]+w:
                dis[v]=dis[u]+w
    change=A(n)
    for i in range(n):
        for u,v,w in edge:
            if dis[v]>dis[u]+w:
                dis[v]=dis[u]+w
                change[v]=1
    return dis

def dij(s,graph):
    d=[inf]*n
    d[s]=0
    heap=[(0,s)]
    while heap:
        dis,u=heappop(heap)
        if dis>d[u]:
            continue
        for v,w in graph[u]:
            if d[v]>d[u]+w:
                d[v]=d[u]+w
                heappush(heap,(d[v],v))
    return d

#有向拓扑，编号1-n
def topo(n):
    q=deque()
    res=[]
    for i in range(1,n+1):
        if ind[i]==0:
            q.append(i)
            res.append(i)
    while q:
        u=q.popleft()
        for v in g[u]:
            ind[v]-=1
            if ind[v]==0:
                q.append(v)
                res.append(v)
    return res

def diameter(n,g):
    vis=A(n)
    d=A(n)
    def dfs(u):
        vis[u]=1
        for v in g[u]:
            if not vis[v]:
                d[v]=d[u]+1
                dfs(v)
    dfs(0)
    ma=-1
    for i in range(n):
        if d[i]>ma:
            r=i
            ma=d[i]
    vis=A(n)
    d=A(n)
    dfs(r)
    return max(d)
#############################################################
def Manacher(s):#(0,0)对应res[2];(0,1)对应res[3];原长对应半径减1
    n=len(s)
    ss=['$','#']
    for x in s:
        ss.append(x)
        ss.append('#')
    ss.append('!')
    res=A(2*n+3,1)
    rm=0
    for i in range(2,2*n+1):
        if i<=rm:
            j=2*im-i
            res[i]=fmin(res[j],rm-i+1)
        while ss[i+res[i]]==ss[i-res[i]]:
            res[i]+=1
        if i+res[i]-1>rm:
            im=i 
            rm=i+res[i]-1
    return res

def z_algorithm(s):
    n = len(s)
    if n == 0:return []
    z = [0]*n
    j = 0
    for i in range(1, n):
        z[i] = 0 if j + z[j] <= i else min(j + z[j] - i, z[i - j])
        while i + z[i] < n and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if j + z[j] < i + z[i]:
            j = i
    z[0] = n
    return z
def getnext(s):
    n=len(s)
    nxt=[-1]*(n+1)
    k=-1
    i=0
    while i<n:
        if k==-1 or s[i]==s[k]:
            nxt[i+1]=k+1
            i+=1
            k=nxt[i]
        else:
            k=nxt[k]
    #next val
    '''
    for i in range(1,n):
        if s[i]==s[nxt[i]]:
            nxt[i]=nxt[nxt[i]]'''
    return nxt

#s1主串，s2模式串
def kmp(s1,s2,nxt=None,i=0):
    #nxt=getnext(s2)
    l1,l2=len(s1),len(s2)
    j=0
    while i<l1 and j<l2:
        if j==-1 or s1[i]==s2[j]:
            i+=1
            j+=1
        else:
            j=nxt[j]
    return j
    '''if j==l2:
        return i-j
    return -1'''

@bootstrap
def dfs(u,p):
    for v in g[u]:
        if v!=p:
            yield dfs(v,u)
    yield None

from random import randint,shuffle
def ra(n,a,b):
    return [randint(a,b) for i in range(n)]
mod=998244353


t=N()
for i in range(t):
    n,m=RL()
    ans=c2(n)
    for i in range(m):
        l,r=RL()
        ans-=(r-l-1)*fmin(i+1,m-i)
        if i:
            ans-=(l-lr-1)*fmin(i,m-i)
        lr=r
    ans-=c2(m+1)
    print(ans)



'''                 
sys.setrecursionlimit(200000)
sys.stdout.flush()
import threading
threading.sta1ck_size(10**8)
t=threading.Thr
ead(target=main)
t.start()
t.join()



'''

