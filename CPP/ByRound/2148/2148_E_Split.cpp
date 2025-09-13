/*
 * Problem URL : https://codeforces.com/contest/2148/problem/E
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
ios::sync_with_stdio(0);cin.tie(0);
int t;cin>>t;
while(t--){
int n,k;cin>>n>>k;
vector<int>a(n),cnt(n+1);
for(int i=0;i<n;i++){
cin>>a[i];
cnt[a[i]]++;
}
bool ok=1;
for(int i=1;i<=n;i++)if(cnt[i]%k){ok=0;break;}
if(!ok){cout<<"0\n";continue;}
long long ans=0;
vector<int>freq(n+1,0);
int left=0;
for(int right=0;right<n;right++){
freq[a[right]]++;
while(left<=right&&freq[a[right]]>cnt[a[right]]/k){
freq[a[left]]--;
left++;
}
ans+=right-left+1;
}
cout<<ans<<"\n";
}
return 0;
}