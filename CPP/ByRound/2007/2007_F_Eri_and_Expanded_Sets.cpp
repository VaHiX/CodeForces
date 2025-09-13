/*
 * Problem URL : https://codeforces.com/contest/2007/problem/F
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
#define ll long long
#define F first
#define S second
using namespace std;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int inf = 1e9;



int main(){
    ios_base::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);

    int Tc = 1; cin>>Tc;
    while(Tc--){
        int n; cin>>n;
        vector<int> a(n);
        for(int i=0; i<n; ++i)cin>>a[i]; --n;
        for(int i=0; i<n; ++i)a[i] = abs(a[i+1]-a[i]);
        vector<int> R(n+1, n);
        for(int i=n-1; i>=0; --i)R[i] = ((a[i]>0)?i:R[i+1]);
        vector<int> Val(n+1, a[0]);
        int l=0, r=0, mid=0, rt=0;
        ll Ans = 1, Cnt = 1;
        for(int i=0; i<n; ++i){
            if(R[i] == i){
                while(l<i){
                    if(l+1 > r)rt = __gcd(a[++r], rt); ++l;
                    if(l>mid){
                        rt = 0, mid = r, Val[mid] = a[mid];
                        for(int j=mid-1; j>=l; --j)Val[j] = __gcd(Val[j+1], a[j]);
                    }
                }
                while(r<n && __builtin_popcount(__gcd(rt, Val[l]))>1)rt = __gcd(a[++r], rt);
                Ans += (n-r)*Cnt + 1LL; Cnt = 1;
            }
            else Ans += R[i] - i + 1LL, ++Cnt;
        }
        cout<<Ans<<'\n';
    }
    return 0;
}
