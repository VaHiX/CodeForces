/*
 * Problem URL : https://codeforces.com/contest/510/problem/C
 * Submit Date : 2025-09-05
 */

#include<bits/stdc++.h>
using namespace std;
int n,i,j,p,L,G[128][128],w[128],df[100];
string s[100],A;
char c,d;
int main(){
for(cin>>n;i<n;i++)cin>>s[i];
for(j=0;j<100;j++)
for(p=i=0;i<n;i++)
if(s[i].length()>j){
if(!df[i]&&s[i][j]!=p)G[p][s[i][j]]=1,df[i]=i>0;
p=s[i][j];
}else if(!(p=0)&&i&&!df[i])goto hell;
while((L=A.length())<26){
for(c='a';c<='z';c++)if(!w[c]){
for(d='a';d<='z'&&!G[d][c];d++);
if(d>'z')for(A+=c,w[c]=1,d='a';d<='z';G[c][d++]=0);
}
if(A.length()==L){
hell:
A="Impossible";
break;
}
}
cout<<A<<endl;
}

    	  		   				 			     	 		 	