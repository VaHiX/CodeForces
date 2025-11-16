// Problem: CF 2167 A - Square?
// https://codeforces.com/contest/2167/problem/A

import java.util.Scanner

/**
 * Problem: Determine if four given stick lengths can form a square.
 * 
 * Approach:
 * - A square has all four sides of equal length.
 * - Therefore, we simply check if all four input values are equal.
 * 
 * Time Complexity: O(1) - constant time for each test case.
 * Space Complexity: O(1) - only using a fixed number of variables.
 */
fun main() {
    val sc = Scanner(System.`in`)
    val t = sc.nextInt()
    repeat(t) {
        val a = sc.nextInt()
        val b = sc.nextInt()
        val c = sc.nextInt()
        val d = sc.nextInt()
        // Check if all four sides are equal to form a square
        if (a == b && b == c && c == d) println("YES") else println("NO")
    }
}


// https://github.com/VaHiX/CodeForces/