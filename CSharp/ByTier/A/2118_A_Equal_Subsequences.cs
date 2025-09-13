using System;

class Program {
    static void Main() {
        int t = int.Parse(Console.ReadLine());
        while (t-- > 0) {
            var parts = Console.ReadLine().Split();
            int n = int.Parse(parts[0]);
            int k = int.Parse(parts[1]);
            Console.WriteLine(new string('1', k) + new string('0', n - k));
        }
    }
}
