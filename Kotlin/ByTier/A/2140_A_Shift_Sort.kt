// Problem: CF 2140 A - Shift Sort
// https://codeforces.com/contest/2140/problem/A

/*
 * Problem: Sort Binary String with Shift Operations
 *
 * Algorithm/Technique: Greedy approach with counting
 *
 * Time Complexity: O(n) per test case, where n is the length of the string
 * Space Complexity: O(1) additional space (excluding input)
 *
 * Description:
 * Given a binary string, we can perform operations that shift three characters cyclically.
 * The goal is to find the minimum number of such operations to sort the string.
 * 
 * Key Insight:
 * Since we are only dealing with '0's and '1's, sorting means placing all '0's before all '1's.
 * We can use greedy approach: for each '0' in prefix of string (before all 1's), 
 * if it is misplaced (i.e. appears after a '1'), we must perform an operation to move it back.
 * This count tells us number of operations needed.
 */

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val n = readLine()!!.toInt() // Read length of string
        val s = readLine()!! // Read binary string
        
        val count = s.count { it == '0' } // Count total number of 0s in the string
        var ans = 0 // Initialize answer counter
        
        // For each of the first `count` characters, check if they are '1'
        // If so, increment operation count (as these '1's need to be moved past '0's)
        for (i in 0 until count) {
            if (s[i] == '1') {
                ans++
            }
        }
        
        println(ans) // Print result for current test case
    }
}


// https://github.com/VaHiX/codeForces/