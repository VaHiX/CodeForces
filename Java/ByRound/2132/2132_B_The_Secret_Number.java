// Problem: CF 2132 B - The Secret Number
// https://codeforces.com/contest/2132/problem/B

/*
B. The Secret Number

Problem Description:
Given a number n = x + y where y is x appended with one or more zeros,
find all possible values of x such that the equation holds.

Approach/Algorithm:
- For each test case n, we iterate through numbers of the form 11...1 (with increasing digits).
- These numbers are used to form potential divisors (e.g., 11, 111, 1111, etc.).
- For a divisor d, if n % d == 0, then x = n / d is a valid solution.
- We collect all such x values and output them in ascending order.

Time Complexity: O(log(n) * log(n)) per test case
Space Complexity: O(log(n)) for storing results

*/
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t-- > 0) {
            long r = sc.nextLong(); // input number n
            long d = 11; // start with 11, the smallest number of form 11...1
            ArrayList<Long> ans = new ArrayList<>();
            while (r >= d) { // continue while d <= r
                if (r % d == 0) { // check if d divides r evenly
                    ans.add(r / d); // store candidate x
                }
                d = (d - 1) * 10 + 1; // generate next number of form 11...1
            }
            System.out.println(ans.size()); // print count of solutions
            for (int i = ans.size() - 1; i >= 0; i--) { // print in ascending order
                System.out.print(ans.get(i) + " ");
            }
            System.out.println();
        }
        sc.close(); // close scanner
    }
}


// https://github.com/VaHiX/codeForces/