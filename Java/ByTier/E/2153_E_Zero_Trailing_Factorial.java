// Problem: CF 2153 E - Zero Trailing Factorial
// https://codeforces.com/contest/2153/problem/E

import java.io.*;
import java.util.*;
public class factorial {
  static class F {
    final InputStream in;
    final byte[] b = new byte[1 << 16];
    int p = 0, q = 0;
    F(InputStream is){in=is;}
    int r() throws IOException {
      if (p>=q){q=in.read(b);p=0; if(q<=0) return -1;}
      return b[p++];
    }
    long nl() throws IOException {
      int c=r(); while(c<=32) c=r();
      long s=0; int m=1;
      if (c=='-'){m=-1;c=r();}
      while(c>32){s=s*10+(c-'0'); c=r();}
      return s*m;
    }
    int ni() throws IOException { return (int)nl(); }
  }
  static int[] ps;
  static int pc;
  static void sieve(int lim){
    boolean[] v=new boolean[lim+1];
    ArrayList<Integer> a=new ArrayList<>();
    for(int i=2;i<=lim;i++){
      if(!v[i]){
        a.add(i);
        if((long)i*i<=lim){
          for(int j=i*i;j<=lim;j+=i) v[j]=true;
        }
      }
    }
    pc=a.size();
    ps=new int[pc];
    for(int i=0;i<pc;i++) ps[i]=a.get(i);
  }
  static boolean isPrime(int x){
    if(x<2) return false;
    for(int i=0;i<pc;i++){
      int p=ps[i];
      long pp=(long)p*p;
      if(pp>x) break;
      if(x%p==0) return false;
    }
    return true;
  }
  static int vpFact(long n,int p){
    long s=0;
    while(n>0){ n/=p; s+=n; }
    return (int)s;
  }
  static int emax(long m,int p){
    int e=0;
    long cur=1;
    while(cur<=m/p){ cur*=p; e++; }
    return e;
  }
  public static void main(String[] args) throws Exception{
    F f=new F(System.in);
    int t=f.ni();
    int LIM=40000;
    sieve(LIM);
    StringBuilder sb=new StringBuilder();
    while(t-->0){
      int n=f.ni();
      long m=f.nl();
      int P=n;
      while(!isPrime(P)) P--;
      if(P==n){ sb.append(0).append('\n'); continue; }
      int cap=1024, sz=0;
      int[] key=new int[cap];
      int[] del=new int[cap];
      int[] B=new int[cap];
      int[] E=new int[cap];
      long ans=0;
      sz = addNum(n, n, m, key, del, B, E, sz);
      for(int x=n-1;x>=P;x--){
        int best=Integer.MAX_VALUE;
        for(int i=0;i<sz;i++){
          int d=del[i];
          if(d==0) continue;
          int a=B[i]-d;
          int s=E[i];
          int bB=B[i];
          for(int e=1;e<=s;e++){
            int aa=a/e;
            int bb=bB/e;
            if(aa<bb){
              if(aa<best) best=aa;
              if(best==0) break;
            }
          }
          if(best==0) break;
        }
        ans+=best;
        if(x>P) sz = addNum(x, n, m, key, del, B, E, sz);
      }
      sb.append(ans).append('\n');
    }
    System.out.print(sb.toString());
  }
  static int addNum(int y,int n,long m,int[] key,int[] del,int[] B,int[] E,int sz){
    long z=y;
    for(int i=0;i<pc;i++){
      int p=ps[i];
      long pp=(long)p*p;
      if(pp>z) break;
      if(z%p==0){
        int c=0;
        while(z%p==0){ z/=p; c++; }
        int idx=idxOf(key,sz,p);
        if(idx<0){
          if(sz==key.length){
            int ns=key.length<<1;
            key=Arrays.copyOf(key,ns);
            del=Arrays.copyOf(del,ns);
            B=Arrays.copyOf(B,ns);
            E=Arrays.copyOf(E,ns);
          }
          key[sz]=p;
          del[sz]=0;
          B[sz]=vpFact(n,p);
          E[sz]=emax(m,p);
          idx=sz++;
        }
        del[idx]+=c;
      }
    }
    if(z>1){
      int p=(int)z;
      int idx=idxOf(key,sz,p);
      if(idx<0){
        if(sz==key.length){
          int ns=key.length<<1;
          key=Arrays.copyOf(key,ns);
          del=Arrays.copyOf(del,ns);
          B=Arrays.copyOf(B,ns);
          E=Arrays.copyOf(E,ns);
        }
        key[sz]=p;
        del[sz]=0;
        B[sz]=vpFact(n,p);
        E[sz]=emax(m,p);
        idx=sz++;
      }
      del[idx]++;
    }
    return sz;
  }
  static int idxOf(int[] a,int sz,int v){
    for(int i=0;i<sz;i++) if(a[i]==v) return i;
    return -1;
  }
}


// https://github.com/VaHiX/CodeForces/