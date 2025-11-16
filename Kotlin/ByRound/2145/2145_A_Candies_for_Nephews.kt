// Problem: CF 2145 A - Candies for Nephews
// https://codeforces.com/contest/2145/problem/A

/*
Problem: A. Candies for Nephews
Purpose: Determine the minimum number of additional candies needed so that n candies can be evenly distributed among 3 nephews.

Algorithm/Technique:
- Mathematical approach using modular arithmetic
- For a given number of candies n, we calculate how many more are needed to make it divisible by 3
- If n % 3 == 0, no additional candies needed
- If n % 3 == 1, need 2 more (to reach next multiple of 3)
- If n % 3 == 2, need 1 more (to reach next multiple of 3)

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - constant space used

Input:
- t test cases
- For each test case: integer n (number of candies)

Output:
- Minimum additional candies needed for even distribution among 3 nephews
*/

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read number of candies
        println((3 - n % 3) % 3) // Calculate and print minimum additional candies needed
    }
}


// https://github.com/VaHiX/CodeForces/