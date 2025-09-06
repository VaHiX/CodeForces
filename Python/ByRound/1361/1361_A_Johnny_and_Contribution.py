# Contest 1361, Problem A: Johnny and Contribution
# URL: https://codeforces.com/contest/1361/problem/A

import math
import sys
from bisect import bisect_left,bisect_right
from collections import defaultdict as dd
from collections import deque, Counter
from heapq import heappop,heappush,heapify,merge
from itertools import permutations, accumulate, product
from math import gcd,sqrt,ceil
toBin=lambda x:bin(x).replace("0b","")
I=lambda:map(int,input().split())
inf=float("inf");DIRS=[[1,0],[-1,0],[0,1],[0,-1]];CHARS="abcdefghijklmnopqrstuvwxyz";MOD=10**9+7;
input=sys.stdin.readline
# Uncomment below to use comb and change FACTMX
# FACTMX=9*10**6;fact=[1]*FACTMX
# for i in range(2, FACTMX):fact[i]=((fact[i-1]*i)%MOD)
# def comb(n,r):return (fact[n]*pow(fact[r]*fact[n-r],MOD-2,MOD))%MOD if n>=r else 0

class UnionFind:
    def __init__(self,n,A):self.p=list(range(n));self.rank=A;self.mx=0
    def find(self,x):
        tmp=[]
        while x!=self.p[x]:tmp.append(x);x=self.p[x]
        for y in tmp:self.p[y]=x
        return x
    def union(self,x, y):
        px,py=self.find(x),self.find(y)
        if px==py:return 0
        if self.rank[px]>=self.rank[py]:self.rank[px]+=self.rank[py];self.p[py]=px
        else:self.rank[py]+=self.rank[px];self.p[px]=py
        # self.mx=max(self.mx,self.rank[px])
        return max(self.rank[px],self.rank[py])
class SegmentTree:
    def __init__(self,n,func):
        self.n=n;self.tree=[0]*2*self.n;self.func=func
    def query(self, l, r):
        l+=self.n;r+=self.n;ans=1#change
        while l<r:
            if l&1:ans=self.func(ans,self.tree[l]);l+=1
            if r&1:r-=1;ans=self.func(ans,self.tree[r])
            l>>=1;r>>=1
        return ans
    def update(self,i,val):
        i+=self.n;self.tree[i]=val
        while i>1:i>>=1;self.tree[i]=self.func(self.tree[i*2],self.tree[i*2+1])
class RangeQueue:
    def __init__(self,fn=min):
        self.inbox=[];self.outbox=[];self.fn=fn
    def mn(self,st):return st[-1][1] if st else 0 #gcd or max= or sum0,mi=inf
    def get_fn(self):return self.fn(self.mn(self.inbox),self.mn(self.outbox))
    def sz(self):return len(self.inbox)+len(self.outbox)
    def push(self,v):
        if not self.inbox:self.inbox.append((v,v))
        else:self.inbox.append((v,self.fn(v,self.mn(self.inbox))))
    def pop(self):
        if len(self.outbox)==0:self.shift()
        self.outbox.pop()
    def shift(self):
        while self.inbox:
            self.outbox.append((self.inbox[-1][0],self.fn(self.inbox[-1][0],self.mn(self.outbox))))
            self.inbox.pop()
_A=True
class SortedList:
    def __init__(A,iterable=[],_load=200):B=_load;C=sorted(iterable);A._len=E=len(C);A._load=B;A._lists=D=[C[A:A+B]for A in range(0,E,B)];A._list_lens=[len(A)for A in D];A._mins=[A[0]for A in D];A._fen_tree=[];A._rebuild=_A
    def _fen_build(B):
        B._fen_tree[:]=B._list_lens;C=B._fen_tree
        for A in range(len(C)):
            if A|A+1<len(C):C[A|A+1]+=C[A]
        B._rebuild=False
    def _fen_update(B,index,value):
        A=index
        if not B._rebuild:
            C=B._fen_tree
            while A<len(C):C[A]+=value;A|=A+1
    def _fen_query(B,end):
        A=end
        if B._rebuild:B._fen_build()
        D=B._fen_tree;C=0
        while A:C+=D[A-1];A&=A-1
        return C
    def _fen_findkth(A,k):
        B=A._list_lens
        if k<B[0]:return 0,k
        if k>=A._len-B[-1]:return len(B)-1,k+B[-1]-A._len
        if A._rebuild:A._fen_build()
        C=A._fen_tree;D=-1
        for F in reversed(range(len(C).bit_length())):
            E=D+(1<<F)
            if E<len(C)and k>=C[E]:D=E;k-=C[D]
        return D+1,k
    def _delete(B,pos,idx):
        A=pos;C=B._lists;E=B._mins;D=B._list_lens;B._len-=1;B._fen_update(A,-1);del C[A][idx];D[A]-=1
        if D[A]:E[A]=C[A][0]
        else:del C[A];del D[A];del E[A];B._rebuild=_A
    def _loc_left(E,value):
        F=value
        if not E._len:return 0,0
        G=E._lists;I=E._mins;B,A=-1,len(G)-1
        while B+1<A:
            C=B+A>>1
            if F<=I[C]:A=C
            else:B=C
        if A and F<=G[A-1][-1]:A-=1
        H=G[A];B,D=-1,len(H)
        while B+1<D:
            C=B+D>>1
            if F<=H[C]:D=C
            else:B=C
        return A,D
    def _loc_right(D,value):
        G=value
        if not D._len:return 0,0
        H=D._lists;J=D._mins;B,E=0,len(H)
        while B+1<E:
            A=B+E>>1
            if G<J[A]:E=A
            else:B=A
        I=H[B];F,C=-1,len(I)
        while F+1<C:
            A=F+C>>1
            if G<I[A]:C=A
            else:F=A
        return B,C
    def add(A,value):
        E=value;C=A._load;F=A._lists;H=A._mins;G=A._list_lens;A._len+=1
        if F:
            B,I=A._loc_right(E);A._fen_update(B,1);D=F[B];D.insert(I,E);G[B]+=1;H[B]=D[0]
            if C+C<len(D):F.insert(B+1,D[C:]);G.insert(B+1,len(D)-C);H.insert(B+1,D[C]);G[B]=C;del D[C:];A._rebuild=_A
        else:F.append([E]);H.append(E);G.append(1);A._rebuild=_A
    def discard(A,value):
        C=value;D=A._lists
        if D:
            E,B=A._loc_right(C)
            if B and D[E][B-1]==C:A._delete(E,B-1)
    def remove(A,value):
        B=value;C=A._len;A.discard(B)
        if C==A._len:raise ValueError('{0!r} not in list'.format(B))
    def pop(A,index=-1):B=index;C,D=A._fen_findkth(A._len+B if B<0 else B);E=A._lists[C][D];A._delete(C,D);return E
    def bisect_left(A,value):B,C=A._loc_left(value);return A._fen_query(B)+C
    def bisect_right(A,value):B,C=A._loc_right(value);return A._fen_query(B)+C
    def count(A,value):B=value;return A.bisect_right(B)-A.bisect_left(B)
    def __len__(A):return A._len
    def __getitem__(A,index):B=index;C,D=A._fen_findkth(A._len+B if B<0 else B);return A._lists[C][D]
    def __delitem__(A,index):B=index;C,D=A._fen_findkth(A._len+B if B<0 else B);A._delete(C,D)
    def __contains__(B,value):
        C=value;A=B._lists
        if A:D,E=B._loc_left(C);return E<len(A[D])and A[D][E]==C
        return False
    def __iter__(A):return(B for A in A._lists for B in A)
    def __reversed__(A):return(B for A in reversed(A._lists)for B in reversed(A))
    def __repr__(A):return'SortedList({0})'.format(list(A))
def bit_count(x):x=(x&0x55555555)+((x>>1)&0x55555555);x=(x&0x33333333)+((x>>2)&0x33333333);x=(x&0x0f0f0f0f)+((x>>4)&0x0f0f0f0f);x=(x&0x00ff00ff)+((x>>8)&0x00ff00ff);x=(x&0x0000ffff)+((x>>16)&0x0000ffff);return x
def query(x,y):
    print("?",x,y,flush=True)
    return list(I())

# DP,BS,Greedy,Graph,UF,Contribution,IE,Game,Reverse simulation,Trie,Bits,SortedList,Caching,Pigeonhole
# NT:Euclidian,modulo,divisors,gcd,lcm
# Trees:Reroot,bottom-up
def main():
    """
    830-to fully understand.
    1->2->3
    4->5
    15m-start with the nodes with topic 1, then topic 2,...
    iterate through all its neighbors to find missing min value.
    then validate it. Maintain a global list of orders.
    1. topic:list of nodes, global list.
    start 20m
    """
    n,m=I();G={i:[] for i in range(n)};res=[];ok=True;mp={i:[] for i in range(n)}
    for _ in range(m):a,b=I();a-=1;b-=1;G[a].append(b);G[b].append(a)
    T=list(I())
    for i in range(n):mp[T[i]-1].append(i)
    for i in range(n):
        x=mp[i]
        for node in x:
            vals=[];mi=1
            for neigh in G[node]:vals.append(T[neigh])
            vals.sort()
            for v in vals:
                if v==mi:mi+=1
            if mi==i+1:res.append(node+1)
            else:ok=False;break;
        if not ok:break;
    if not ok:print(-1)
    else:print(*res)

    """
    630m-any circular dependency, its impossible. topological?
    2->1->3
    ->4->3
    what are the steps? ..we start with the lowest node with no in_degrees and
    keep erasing the edges only if the node is greater. but that might exceed
    TC as we have n nodes and each can have n-1 edges. no we are going through
    U+V, not U*V, actually it is...we know 20m-in certain cases, its impossible
    because there are too many edges. if number of edges>=number of nodes, return -1.
    otherwise, we can proceed. start 21m. WA T2 37m, WA T2 42m.
    50m-the error is to...at 55m basically figured out heap and thought of the edge
    case later..very close. missed the part where sum of nodes and neighbors
    can be visited ocne.
    """
    # for _ in range(int(input())):
    #     n=int(input());tot=0;G={i:[] for i in range(n)};in_degrees=[0]*n;turn=0;vis=0
    #     for i in range(n):
    #         A=list(I());tot+=A[0];
    #         for j in range(1,len(A)):G[A[j]-1].append(i);in_degrees[i]+=1
    #     start=[i for i in range(n) if in_degrees[i]==0];
    #     while start:
    #         heapify(start);A=[*start];start=[]
    #         while A:
    #             node=heappop(A);vis+=1
    #             for neigh in G[node]:
    #                 in_degrees[neigh]-=1
    #                 if in_degrees[neigh]==0:
    #                     if neigh>node:heappush(A,neigh)
    #                     else:start.append(neigh)
    #         turn+=1
    #     if vis!=n:print(-1)
    #     else:print(turn)
    """
    if they meet at cell (i,j), we can calculate their gains up until that point
    and subtract from max gain of endpoint - where they met. we can do this for
    all cells and get its max. 22m start 36m. logic flaw. inclusion-exclusion?
    stuck at finding out the max from a meeting cell in constant time.
    I think the logic itself is wrong. 50m. there are only two ways to access
    the meeting cell.A goes down + B goes left to right OR A goes left to right
    and B goes down and up, but it still goes back to the original question.
    editorial at 57m. so basically had the right idea at 50m, but didn't think
    about creating another dp to calculate each start point. Takeaways: Use m+2,n+2
    dimensions, and didn't think about going the opposite direction.
    """

###### Comment this out for Python 3 + imports at the top #####
if __name__ == "__main__":
    main()

###### Uncomment this for Python 3 (for deep recursion) ######
# from sys import stdin, setrecursionlimit
# import threading
# from collections import defaultdict as dd
# from collections import deque
# setrecursionlimit(5*10**5);input=stdin.buffer.readline;I=lambda:map(int,input().split())
# threading.stack_size(10**8)
# t = threading.Thread(target=main)
# t.start()
# t.join()