// Problem: CF 2156 F1 - Strange Operation (Easy Version)
// https://codeforces.com/contest/2156/problem/F1

/*
Code Purpose:
This solution aims to find the lexicographically smallest permutation possible by performing a specific operation any number of times on a given permutation.
The operation allows selecting three indices i < j < k such that p[i] = max(p[j], p[k]) + 1 and p[i] = min(p[j], p[k]) + 2. 
Then, p[i] is decreased by 2, and p[j] and p[k] are each increased by 1.

Algorithms/Techniques:
- Greedy approach with sorting-like logic
- Tracking indices using an auxiliary array b where b[value] = index
- Repeatedly applying the operation to reduce lexicographical value

Time Complexity: O(n^2)
Space Complexity: O(n)

*/
import java.util.*;
public class Main{
	private static void swap(int[]a,int i,int j,int k){
		int t=a[k];
		a[k]=a[i];
		a[i]=a[j];
		a[j]=t;
	}
	private static void here(int []a,int []b,int i,int j,int k){
			int c[]=new int[2];
			for(int x=1;x<=3;x++){
				if(x%3==0){
					c[0]=a[k];
					c[1]=k;
				}else if(x%3==1){
					c[0]=a[i];
					c[1]=i;
				}else if(x%3==2){
					c[0]=a[j];
					c[1]=j;
				}
				b[c[0]]=c[1]; 
			}
		}
    private static void cc(int a[],int []b,int i,int j, int k){
    	swap(a,i,j,k);
    	here(a,b,i,j,k);
    }
private static boolean check(int j,int i,int a[]){
	return a[i]>a[j];
}
public static void main(String[] args){
	Scanner sc=new Scanner(System.in);
	int t=sc.nextInt();
	while(t-->0){
		int n=sc.nextInt();
		int a[]=new int[n+1];
		int f=1;
		for(int i=0;i<n;i++) a[i+1]=sc.nextInt();
		int b[]=new int[n+1];
		for(int i=0;i<n;i++) b[a[i+1]]=i+1; // b[value] = index of value in array a
		int x=1;
		if(n<3){
		}else{
			while(f==1){
				f=0;x=1;
				while(x+2<=n){
					if(check(x+2,x,b)){ // Check if a[x+2] > a[x] using indices from b
					if(check(x+2,x+1,b)){ // Check if a[x+2] > a[x+1] using indices from b
						cc(a,b,b[x],b[x+1],b[x+2]); // Perform operation
						f=1;
					}}
					x++;
				}
			}
		}
		StringBuilder sb=new StringBuilder();
		for(int i=0;i<n;i++){
			sb.append(a[i+1]);
			if((i+1)<n) sb.append(" ");
		}
		System.out.println(sb.toString());
	}}
}


// https://github.com/VaHiX/CodeForces/