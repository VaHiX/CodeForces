/*
 * Problem URL : https://codeforces.com/contest/2013/problem/C
 * Submit Date : 2025-09-12
 */

#include<bits/stdc++.h>
using namespace std;
int ask(string s){
	cout<<"? "<<s<<endl;
	int op;
	cin>>op;
	return op;
}
void Showball(){
   	int n;
   	cin>>n;
   	string t="";
   	while(t.size()<n)
   	{
   		if(ask(t+'0'))
			t=t+'0';
		else if(ask(t+'1'))	t=t+'1';
		else break;
	}
	while(t.size()<n)
	{
		if(ask('1'+t))
		{
			t='1'+t;
		}
		else t='0'+t;
	}
	cout<<"! "<<t<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--)	Showball();
} 