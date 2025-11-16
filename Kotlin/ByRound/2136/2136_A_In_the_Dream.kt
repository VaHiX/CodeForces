// Problem: CF 2136 A - In the Dream
// https://codeforces.com/contest/2136/problem/A

/*
 * Problem: A. In the Dream
 * Purpose: Determine if a given football score distribution (first and second half) is valid,
 *          under the constraint that no team can score three consecutive goals in a half.
 *
 * Algorithm:
 * - For each half, check if the score can be achieved without violating the "no three consecutive goals" rule.
 * - This is done by verifying whether `high <= (low + 1) * 2`, where low and high are the scores of the two teams,
 *   ensuring that one team isn't too far ahead to have avoided three consecutive goals.
 *
 * Time Complexity: O(1) per test case — constant time operations.
 * Space Complexity: O(1) — only using a few variables regardless of input size.
 */

import java.util.Scanner

fun main() {
    val reader = Scanner(System.`in`)
    val testCase = reader.nextLine()
    for (tc in 1..testCase.toInt()){
        val inputStr = reader.nextLine()
        val inputStrings = inputStr.split(" ")
        val a = inputStrings[0].toInt() // First half RiOI score
        val b = inputStrings[1].toInt() // First half KDOI score
        val c = inputStrings[2].toInt() - a // Second half RiOI score difference
        val d = inputStrings[3].toInt() - b // Second half KDOI score difference
        
        // Check first half validity: ensure no team scored 3+ consecutive goals
        val result = if (a<b) measureDreamIsTrue(a,b) else measureDreamIsTrue(b,a)
        
        if (result == "No"){
            println("No")
        }else{
            // Check second half validity
            if (c<d) println(measureDreamIsTrue(c,d)) else println(measureDreamIsTrue(d,c))
        }
    }
}

/**
 * Helper function to check if score difference is valid under the 'no three consecutive goals' rule.
 * @param low Lower score
 * @param high Higher score
 * @return "Yes" if valid, "No" otherwise
 */
private fun measureDreamIsTrue(low: Int, high: Int): String{
    return if ((low+1)*2>=high) "Yes" else "No"
}


// https://github.com/VaHiX/CodeForces/