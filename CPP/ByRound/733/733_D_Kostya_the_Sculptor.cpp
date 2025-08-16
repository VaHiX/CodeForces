/*
 * Problem URL : https://codeforces.com/problemset/problem/733/D
 * Submit Date : 2025-08-15
 */

#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100003;
struct node{
	int x,y,z,id;
}b[maxn];
int n;
int a[3];
bool cmp(node a,node b){
	if(a.z!=b.z)
		return a.z<b.z;
	if(a.y!=b.y)
		return a.y<b.y;
	return a.x<b.x;
}
int main(){
	int ans=0,id=0,id1=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d%d%d",&a[0],&a[1],&a[2]);
		sort(a,a+3);
		b[i].x=a[0],b[i].y=a[1],b[i].z=a[2];
		if(a[0]>ans){
			ans=a[0];
			id=i;
		}
		b[i].id=i;
	}
	sort(b+1,b+n+1,cmp);
	for(int i=2;i<=n;++i)
		if(b[i].z==b[i-1].z&&b[i].y==b[i-1].y){
			if(min(b[i].x+b[i-1].x,min(b[i].y,b[i-1].y))>ans){
				ans=min(b[i].x+b[i-1].x,min(b[i].y,b[i-1].y));
				id=b[i].id;
				id1=b[i-1].id;
			}
		}
	if(id1)
		printf("2\n%d %d\n",id,id1);
	else
		printf("1\n%d\n",id);
	return 0;
}
		 		    	  			 	      		  	 	