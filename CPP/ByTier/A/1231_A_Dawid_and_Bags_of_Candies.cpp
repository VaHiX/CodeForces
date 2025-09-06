/*
 * Problem URL : https://codeforces.com/contest/1231/problem/A
 * Submit Date : 2025-09-02
 */

#include <iostream>
#include<algorithm>
using namespace std;

int main()
{int arr[4];
cin>>arr[0]>>arr[1]>>arr[2]>>arr[3];
sort(arr,arr+4);
if(arr[0]+arr[3]==arr[1]+arr[2]||arr[0]+arr[1]+arr[2]==arr[3])
    cout<<"YES";
else cout<<"NO";
    return 0;
}
