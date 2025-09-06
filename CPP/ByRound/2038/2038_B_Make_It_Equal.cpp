/*
 * Problem URL : https://codeforces.com/contest/2038/problem/B
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>
using namespace std;

int n,c,d,k,a[200005],b[200005];
typedef long long ll;


int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

int t;
cin>>t;
while(t--)
{
   cin>>n;
   for(int i=0;i<n;i++)
   {
   	cin>>a[i];
   }
   int z=0;
   while(!z)
   {
   	z=1;
   	for(int i=0;i<n;i++)
	   {
	   	if(a[i]&&a[i]+1)z=0;
	   	b[i]+=(a[i]+1)/2;
	   	a[(i+1)%n]+=(a[i]+1)/2;
	   	a[i]=-(a[i]&1);
		}
   }
   z=1;
   int d=2000000001;
   for(int i=0;i<n;i++)
   {
   	if(a[i])z=0;
	   d=min(d,b[i]);
   }
   long long s=0;
   if(!z){cout<<"-1\n";goto bla;
   }
   for(int i=0;i<n;i++)s+=b[i]-d;
   cout<<s<<"\n";
   bla:
   	for(int i=0;i<n+3;i++)b[i]=0;
}


  return 0;
}

