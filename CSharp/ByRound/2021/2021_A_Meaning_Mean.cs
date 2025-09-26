using System;
using System.Linq;

namespace MeaningMean{
    internal class Solution{
        static void Main(string[] args){
            int limit = int.Parse(Console.ReadLine());
            for(int i = 0; i < limit; i++) Solve();
        }
        static void Solve(){
            string size = Console.ReadLine();
            int[] input1 = Console.ReadLine().Split(' ').Select(int.Parse).ToArray();
            Array.Sort(input1);
            int answer = input1[0];
            for(int i = 1; i < input1.Length; i++){
                answer = (answer+input1[i])/2;
            }
            Console.WriteLine(answer);
        }
    }
}