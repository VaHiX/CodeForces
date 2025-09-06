/*
 * Problem URL : https://codeforces.com/contest/906/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
int n,f,s,v[128],w[128];char p,q[100100];void c(int x){int l=strlen(q),r=0,i=0;for(;i<l;++i)v[(int)q[i]]=1;for(i=97;i<123;++i)w[i]|=(v[i]^x),r+=!w[i],v[i]=0;f|=r<2;}main(){for(scanf("%d%*c",&n);n;--n){scanf("%c%*c%s%*c",&p,q);if(p!=46&&n>1)s+=f;c(p<46||(p>46&&n<2));}printf("%d",s);}