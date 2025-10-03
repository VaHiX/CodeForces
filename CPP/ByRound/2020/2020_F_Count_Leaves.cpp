/*
 * Problem URL : https://codeforces.com/contest/2020/problem/F
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
#define il inline
#define ll long long

const int N=3e6+1e5+5,M=3.2e4,K=35,Mod=1e9+7;

int T,S,n,k,d,cnt,tot;
int p[M],id1[M],id2[M],g[M<<1],val[M<<1];
ll fac[N],inv[N],f[K];
bitset<M>isp;

il int mod(int x,int p){return x-x/p*p;}
il ll C(int n,int m){return fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
il int get(int v){return v<=S?id1[v]:id2[n/v];}

il void Euler(int S){
    for(int i=2;i<=S;i++){
        if(!isp[i])p[++cnt]=i;
        for(int j=1,P;(P=p[j])<=S/i;j++){
            isp[i*P]=1;
            if(!mod(i,P))break;
        }
    }
    return ;
}

il ll QuickPow(ll a,int b=Mod-2){
    ll res=1;
    while(b){
        if(b&1)res=res*a%Mod;
        a=a*a%Mod;
        b>>=1;
    }
    return res;
}

il void Init(){
    Euler(31622);
    int N=3e6+1e5;
    fac[0]=1;
    for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i%Mod;
    inv[N]=QuickPow(fac[N]);
    for(int i=N-1;~i;i--)inv[i]=inv[i+1]*(i+1)%Mod;
    return ;
}

il ll SumF(int n,int b){
    int id=get(n);
    ll res=(g[id]-b)*f[1]%Mod;
    for(int i=b+1,P=p[i],pk=P;i<=cnt&&P<=n/P;pk=P=p[++i]){
        for(int j=1;pk<=n/P;j++,pk*=P){
            res=(res+f[j]*SumF(n/pk,i)+f[j+1])%Mod;
        }
    }
    return res;
}

il void Build(){
    cin>>n>>k>>d;
    int l=__lg(n);
    for(int i=1,p=k;i<=l;i++,p+=k)f[i]=C(p+d,d);
    S=sqrt(n),tot=0;
    for(int l=1,r,v;l<=n;l=r+1){
        r=n/(v=n/l);
        if(v<=S)id1[v]=++tot;
        else id2[n/v]=++tot;
        val[tot]=v,g[tot]=v-1;
    }
    for(int j=1,P=2;j<=cnt&&P<=S;P=p[++j]){
        for(int i=1,v;i<=tot&&P<=(v=val[i]/P);i++)g[i]-=g[get(v)]-j+1;
    }
    cout<<(SumF(n,0)+1)%Mod<<"\n";
    return ;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    Init();
    cin>>T;
    while(T--)Build();
    return 0;
}