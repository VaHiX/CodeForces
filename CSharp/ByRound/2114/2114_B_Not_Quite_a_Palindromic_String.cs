
using System;
using System.Collections.Generic;
public class Demo{
    public static void Main(){
            int test = int.Parse(Console.ReadLine());
            while(test>0)
            {
            test--;
            string[] s= Console.ReadLine().Split();
            int n = int.Parse(s[0]);
            int k = int.Parse(s[1]);
            string s1 = Console.ReadLine();
            int o=0,z=0;
            for(int i=0;i<n;i++){
                if(s1[i]=='1')o++;
                else z++;
            }
            k=n-2*k;
            o-=k/2;
            z-=k/2;
            if(o>=0 && z>=0 && o%2==0 && z%2==0)Console.WriteLine("Yes");
            else Console.WriteLine("No");
    }
    }
}