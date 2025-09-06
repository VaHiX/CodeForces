/*
 * Problem URL : https://codeforces.com/contest/1178/problem/A
 * Submit Date : 2025-08-28
 */

#import<ios>
int a[101],n,s,i,p,j,S;main(){for(;scanf("%d",i?a+i:&n)>0;++i)i?i^1?:p=a[i],i==1|2*a[i]<=p?S+=a[i],a[++*a]=i:s+=a[i]:0;if(S>s)for(;j<=*a;++j)printf("%d ",a[j]);else puts("0");}