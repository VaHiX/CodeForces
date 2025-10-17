// Problem: CF 2087 A - Password Generator
// https://codeforces.com/contest/2087/problem/A

/*
 * Problem: Password Generator
 * Algorithm/Techniques: Greedy Construction
 *
 * Time Complexity: O(a + b + c) per test case, which is effectively O(1) since a, b, c <= 10
 * Space Complexity: O(a + b + c) for the output string, which is also effectively O(1)
 *
 * Description:
 * The task is to generate a password that consists of exactly 'a' digits,
 * 'b' uppercase letters, and 'c' lowercase letters such that no two adjacent
 * characters are the same. This is achieved by:
 * 1. Using digits 0 through (a-1) for the first 'a' positions.
 * 2. Using uppercase letters A through (A + b - 1) for next 'b' positions.
 * 3. Using lowercase letters a through (a + c - 1) for last 'c' positions.
 * This greedy approach ensures no immediate adjacency violations, and the result
 * can be proven to satisfy all constraints.
 */

import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().toInt() // Read number of test cases
    repeat(t) {
        val st = StringTokenizer(br.readLine())
        val a = st.nextToken().toInt() // Number of digits required
        val b = st.nextToken().toInt() // Number of uppercase letters required
        val c = st.nextToken().toInt() // Number of lowercase letters required
        
        // Generate 'a' digits: 0, 1, ..., (a-1)
        for (i in 0 until a) {
            print(i)
        }
        
        // Generate 'b' uppercase letters: A, B, ..., (A + b - 1)
        for (i in 1..b) {
            print((64 + i).toChar()) // ASCII value of 'A' is 65, so 64 + i gives correct letter
        }
        
        // Generate 'c' lowercase letters: a, b, ..., (a + c - 1)
        for (i in 1..c) {
            print((96 + i).toChar()) // ASCII value of 'a' is 97, so 96 + i gives correct letter
        }
        
        println() // Print new line after each test case
    }
}


// https://github.com/VaHiX/codeForces/