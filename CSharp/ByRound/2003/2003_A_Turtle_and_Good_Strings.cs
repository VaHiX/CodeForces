using System;
namespace rabbi{
      class Test {
            public static void Main(string[] args) {
                  int T = Convert.ToInt32(Console.ReadLine());
                  while(T > 0) {
                        int n = Convert.ToInt32(Console.ReadLine());
                        string s = Console.ReadLine();
                        if(s[0] != s[n - 1]) {
                              Console.WriteLine("YES");
                        } else {
                              Console.WriteLine("NO");
                        }
                        T--;
                  }
            }

      }
}