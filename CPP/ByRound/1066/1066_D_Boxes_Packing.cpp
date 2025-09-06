/*
 * Problem URL : https://codeforces.com/contest/1066/problem/D
 * Submit Date : 2025-08-31
 */

#include<stdio.h>
#define max 200000
int main()
{ int n,m,k,i,w,number;
  int a[max];
  scanf("%d%d%d",&n,&m,&k);
  for(i=0;i<n;i++)
  scanf("%d",a+i);
  for(i=n-1,w=0,number=0;i>=0;i--)
  {
  w+=a[i];
  if(w>k&&number<m-1)
   { w=0;
     w+=a[i];
	 number++;
   }
  if(w>k&&number==m-1)
  break;
  }
 printf("%d\n",n-1-i);
 return 0;
 }