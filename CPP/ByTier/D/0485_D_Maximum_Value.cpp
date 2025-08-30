#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
int n,a[maxn]={0},maxx,j,ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
    j=n-1;
    for(int i=n;i>1;i--)
    {
        maxx=0;
        while(j>=1&&(a[i]%a[j]>=maxx))
        {
            maxx=a[i]%a[j];
            j--;
        }
        ans=max(ans,maxx);
        j++;
        if(j>=i)j=i-1;
    }
	printf("%d",ans);
	return 0;
}
      				  	 	   	       	 	