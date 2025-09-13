using System;

class Program {
    // This method will be responsible for solving a single test case
    static void Solve() {
        // Read the integer n (length of the strings a and b)
        int n = int.Parse(Console.ReadLine());
        
        // Read the strings a and b
        string a = Console.ReadLine();
        string b = Console.ReadLine();

        // Initialize two sums to track alternating values from a and b
        long sum1 = 0, sum2 = 0;

        // Loop over each index of the strings a and b
        for (int i = 0; i < n; ++i) {
            // If the index i is even, we add values from string a and b to sum1 and sum2 accordingly
            if (i % 2 == 0) {
                sum1 += a[i] - '0'; // Convert char to integer and add to sum1
                sum2 += b[i] - '0'; // Convert char to integer and add to sum2
            } else {
                sum1 += b[i] - '0'; // Convert char to integer and add to sum1
                sum2 += a[i] - '0'; // Convert char to integer and add to sum2
            }
        }

        // Calculate the number of slots available for sum1 and sum2
        long numBSlots1 = n / 2;
        long numBSlots2 = (n + 1) / 2;

        // Output "YES" if both sums are within the available slots, otherwise "NO"
        Console.WriteLine((sum1 <= numBSlots1 && sum2 <= numBSlots2) ? "YES" : "NO");
    }

    // Main method where the program starts execution
    static void Main() {
        // Read the number of test cases
        int t = int.Parse(Console.ReadLine());

        // Execute the Solve method for each test case
        while (t-- > 0) {
            Solve();
        }
    }
}
