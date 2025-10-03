/*
 * Problem URL : https://codeforces.com/contest/2018/problem/D
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>
using namespace std;

int a[200010],l[200010],r[200010],f[200010];
vector<int> u;
bool b[200010];

int lms(int x){
    return l[x]==l[l[x]]?l[x]:l[x]=lms(l[x]);
}

int rms(int x){
    return r[x]==r[r[x]]?r[x]:r[x]=rms(r[x]);
}

inline bool check(int l,int r){
    if(f[l]<=r)return true;
    if((r-l+1)%2==0 && f[l+1]<=r)return true;
    return false;
}

int main(){
    int t,n;
    ios::sync_with_stdio(false);cin.tie(nullptr);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i],l[i]=r[i]=i;
            u.emplace_back(i);
        }
        sort(u.begin(),u.end(),
            [&](int x,int y){return a[x]>a[y];});
        memset(f,0x3f,(n+5)<<2);
        for(int i=n;i;i--)
            {f[i]=f[i+2];if(a[i]==a[u[0]])f[i]=i;}
        int ans=0,tot=0,cnt=0;
        for(const int &i:u){
            b[i]=true;
            if(b[i-1]){
                tot-=(i-lms(i-1)+1)/2;
                cnt-=check(lms(i-1),i-1);
                l[i]=lms(i-1);r[i-1]=rms(i);
            }
            if(b[i+1]){
                tot-=(rms(i+1)-i+1)/2;
                cnt-=check(i+1,rms(i+1));
                r[i]=rms(i+1);l[i+1]=lms(i);
            }
            tot+=(rms(i)-lms(i)+2)/2;
            cnt+=check(lms(i),rms(i));
            ans=max(ans,a[u[0]]+a[i]+tot-!cnt);
        }
        cout<<ans<<'\n';
        u.clear();memset(b,0,n+5);
    }
    return 0;
}