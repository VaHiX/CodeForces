/*
 * Problem URL : https://codeforces.com/contest/655/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a,b,c,d,s1,s2;
	cin>>a>>b>>c>>d;
	for(int i=0;i<2;i++)
		if(a[i]!='X')s1+=a[i];
	for(int i=1;i>=0;i--)
		if(b[i]!='X')s1+=b[i];
	for(int i=0;i<2;i++)
		if(c[i]!='X')s2+=c[i];
	for(int i=1;i>=0;i--)
		if(d[i]!='X')s2+=d[i];
	s1+=s1;
	if(s1.find(s2)!=-1 )cout<<"YES";
	else cout<<"NO";
	return 0; 
}
 	  	   	 	  	 	  	  		     	