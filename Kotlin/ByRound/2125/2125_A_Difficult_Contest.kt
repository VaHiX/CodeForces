// Problem: CF 2125 A - Difficult Contest
// https://codeforces.com/contest/2125/problem/A

/*
 * Problem: A. Difficult Contest
 * 
 * Purpose: Rearrange the characters in a string such that it does not contain "FFT" or "NTT" as a substring.
 *          If the input is already safe, leave it unchanged.
 *
 * Algorithm:
 *   1. For each test case:
 *      - Count frequency of each character (A-Z).
 *      - Build result string by appending characters in order A to Z.
 *      - If "FFT" or "NTT" exists in the string:
 *          - Reverse the string and output it.
 *      - Otherwise, output the string as is.
 *
 * Time Complexity: O(n) where n is the total length of all input strings across test cases.
 * Space Complexity: O(1) as we use fixed-size arrays (26 elements for alphabet).
 */

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val s = readLine()!! // Read current test string
        val freq = IntArray(26) // Array to store frequency of each character (A-Z)
        for (c in s) {
            freq[c - 'A']++ // Increment frequency for character c
        }
        val result = StringBuilder() // Build final string character by character
        for (i in 0 until 26) {
            repeat(freq[i]) { // Append character i+'A' freq[i] times
                result.append('A' + i)
            }
        }
        val output = result.toString() // Convert to string
        if ("FFT" in output || "NTT" in output) { // Check for forbidden substrings
            val chars = output.toCharArray()
            chars.reverse() 
            println(String(chars)) // Reverse and print
        } else {
            println(output) // Print as is
        }
    }
}


// https://github.com/VaHiX/CodeForces/