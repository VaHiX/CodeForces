/*
 * Problem URL : https://codeforces.com/contest/1479/problem/A
 * Submit Date : 2025-09-01
 */

#include <iostream>
using namespace std;

int main(){
int n;cin>>n;
int l=1,r=n;
while(l<r){
int a,b,mid=(l+r)/2;
cout<<"? "<<mid<<endl;
cin>>a;
cout<<"? "<<mid+1<<endl;
cin>>b;
if(a<b)r=mid;
else l=mid+1;
}
cout<<"! "<<l<<"\n";
return 0;
}