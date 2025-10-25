// Problem: CF 2140 B - Another Divisibility Problem
// https://codeforces.com/contest/2140/problem/B

/*
B. Another Divisibility Problem

Purpose:
This program solves a problem where, given a positive integer x, we need to find another positive integer y such that the concatenation of x and y (denoted as x#y) is divisible by the sum x + y.

Algorithm/Techniques:
- Observation: For any x, if we set y = x / 2 when x is even, or y = 2 * x when x is odd, this satisfies the divisibility condition.
- This approach works because it ensures a specific mathematical relationship between x and y that makes x#y divisible by x + y.

Time Complexity: O(t), where t is the number of test cases. Each test case takes constant time.
Space Complexity: O(1) excluding the output buffer, as we only use a few variables regardless of input size.

Input:
- First line contains number of test cases t
- Each test case contains a single integer x (1 ≤ x < 10^8)

Output:
- For each test case, print a positive integer y (1 ≤ y < 10^9) such that x#y is divisible by x + y.
*/

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt() // Read number of test cases
    val sb = StringBuilder()
    repeat(t) {
        val x = br.readLine().toLong() // Read current test case value
        
        // Compute y based on whether x is even or odd
        val y = if (x % 2 == 0L) x / 2 else 2 * x // Key logic to satisfy divisibility condition
        
        sb.append(y).append("\n") // Append result to output buffer
    }
    print(sb.toString()) // Print final output
}


// https://github.com/VaHiX/codeForces/