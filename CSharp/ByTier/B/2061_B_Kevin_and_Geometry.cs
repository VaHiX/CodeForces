using System;
using System.Linq;
using System.Collections.Generic;

class DJ{
    
    void solve(){
        int n = Convert.ToInt32(Console.ReadLine());
        List<int> a = Console.ReadLine().Split(' ').Select(s => int.Parse(s)).ToList();
        a.Sort();
        int A = -1, B = -1, C = -1;
        for(int i = n - 1; i >= 1 ; i --){
            if(a[i] == a[i - 1]){
                A = a[i];
                a.RemoveAt(i - 1);
                a.RemoveAt(i - 1);
                break;
            }
        }
        for(int i = 1; i < n - 2;i ++){
            if(C == -1 || C - B > a[i] - a[i - 1]){
                C = a[i];
                B = a[i - 1];
            }
        }
     
        if(A == -1 || 2 * A + B <= C){
            Console.WriteLine(-1);
            return;
        }
        Console.WriteLine(A + " " + A + " " + B + " " + C);
    }
    static void Main(){
        int T = 1;
        T = Convert.ToInt32(Console.ReadLine());
        DJ d = new DJ();
        while(T-- > 0){
            d.solve();
        }
    }
}