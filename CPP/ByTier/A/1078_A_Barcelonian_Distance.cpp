/*
 * Problem URL : https://codeforces.com/contest/1078/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <math.h>
using namespace std;
long double a,b,c;
const double EPS=1e-9;
struct point{
	long double x,y;
	point operator-(const point&a)const{
		return {x-a.x,y-a.y};
	}
}p1[3],p2[3],o1,o2;
int t1,t2;
long double abs(point a){
	return sqrt(a.x*a.x+a.y*a.y);
}
long double dis(point a,point b){
	return abs(a-b);
}
int main(){
	cin >> a >> b >> c;
	cin >> o1.x >> o1.y >> o2.x >> o2.y;
	long double ans=fabs(o1.x-o2.x)+fabs(o1.y-o2.y);
	if (fabs(a)<EPS||fabs(b)<EPS){
		printf("%.10Lf",ans);
		return 0;
	}
	p1[++t1]={o1.x,(-c-a*o1.x)/b};
	p2[++t2]={o2.x,(-c-a*o2.x)/b};
	p1[++t1]={(-c-b*o1.y)/a,o1.y};
	p2[++t2]={(-c-b*o2.y)/a,o2.y};
	for (int i=1;i<=t1;i++)
		for (int j=1;j<=t2;j++){
			ans=min(ans,dis(p1[i],p2[j])+dis(o1,p1[i])+dis(o2,p2[j]));
		}
	printf("%.10Lf",ans);
}