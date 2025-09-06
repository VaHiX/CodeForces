// See https://aka.ms/new-console-template for more information
//Console.WriteLine("Hello, World!");
using System;
using System.Collections.Generic;
public class MyDemo{

	  public static void solve(){
		   string[] input = Console.ReadLine().Split();
		   int n = int.Parse(input[0]);
		   int k = int.Parse(input[1]);
		   int[] a = Array.ConvertAll(Console.ReadLine().Split(),int.Parse);
		   if(n==k){
			    for(int i=1;i<n;i+=2){
					if(a[i]!=(i+1)/2){
						Console.WriteLine(i/2+1);
						return;
					}
				}
				Console.WriteLine(n/2+1);
				return;
		   }
		   for(int i=n-1;i>=1;i--){
			int x = 2 + n-1-i;
			if(x>=k){
				if(a[i]!=1){
					Console.WriteLine(1);
					return;
				}
			}
		   }
		   Console.WriteLine(2);
	  }
	  public static void Main(){ 
        int t = int.Parse(Console.ReadLine()); 
	  	   for(int i=0;i<t;i++){
	  	   	  solve();
	  	   }
	  }
}