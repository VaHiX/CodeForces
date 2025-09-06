/*
 * Problem URL : https://codeforces.com/contest/819/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>

using namespace std;

int a,b,l,r;

int main() {
	cin>>a>>b>>l>>r;

    int cl = --l / (a + b);
    int pl = l % (a + b);
	int cr = --r / (a + b);
    int pr = r % (a + b);
    
    if(cl==cr) {
        cout<<min(r-l+1,max(a-pl,1));
        return 0;
    }

    if(a<=b){
		if(cl < cr - 1) {
            cout << a + 1 << "\n";
        }
		else {
            int x=max(1,a-pl);
			int y=min(a,pr+1);
            cout<<min(a,x+y)+(y==a);
		}
        return 0;
	}

    int d = a - b;
    if(cl==cr-1) {
        cout<<max(1,min(d,a-pl))+min(a,pr+1);
        return 0;
    }

    if(cl==cr-2) {
        cout<<a+max(1,d+min(0,pr-a+1+max(0,a-pl)));
        return 0;
    }
    
    cout << a + d << "\n";
}/*1692389113.4067018*/