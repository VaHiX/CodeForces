// Problem: CF 2106 A - Dr. TC
// https://codeforces.com/contest/2106/problem/A

/*
 * Problem: Count total number of '1's in a grid formed by flipping each character 
 *          of a binary string s in turn to create n rows.
 *
 * Algorithm:
 *   - For a binary string s of length n:
 *     - Each row i (1-based) is s with the i-th character flipped.
 *     - Total number of 1s = sum of 1s across all rows.
 *   
 *   Observations:
 *     - Let count of '1's in s be c.
 *     - Then, count of '0's in s is (n - c).
 *     - In the grid, for each position j:
 *       - If s[j] == '1', it contributes 1 to row i where i != j, and 0 to row j.
 *       - If s[j] == '0', it contributes 0 to row i where i != j, and 1 to row j.
 *     - So total number of 1s = c * n - (c - (n - c)).
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

fun solve() {
    val n = readln().toInt() // Read length of binary string
    val s = readln()        // Read the binary string
    val c = s.count { it == '1' } // Count number of 1s in s
    println(c * n - (c - (n - c))) // Compute and print total 1s in grid
}

fun main() {
    repeat(readln().toInt()) { // Repeat for each test case
        solve()
    }
}


// https://github.com/VaHiX/CodeForces/