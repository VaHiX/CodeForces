// Problem: CF 1571 A - Sequence of Comparisons
// https://codeforces.com/contest/1571/problem/A

/*
 * Problem: Determine the relationship between the first and last elements of an array
 *          based on a sequence of comparisons between adjacent elements.
 *
 * Approach:
 * - Count the number of '>' and '<' characters in the input string.
 * - If both '>' and '<' exist, the relationship between first and last elements cannot be determined
 *   because there may be multiple valid sequences (e.g., a sequence can go up and down).
 * - If only '>' exists, then the first element is greater than the last.
 * - If only '<' exists, then the first element is less than the last.
 * - If neither '>' nor '<' exists, all elements are equal.
 *
 * Time Complexity: O(n), where n is the length of the input string.
 * Space Complexity: O(1), only using a few variables for counting and processing.
 */

fun main() {
  repeat(readLine()!!.toInt()) {
    var s = readLine()!!
    var a = s.count({ it == '>' })  // Count of '>' characters
    var b = s.count({ it == '<' })  // Count of '<' characters
    if (a > 0 && b > 0) println("?")  // If both > and < exist, ambiguity
    else if (a > 0) println(">")      // If only > exists, first > last
    else if (b > 0) println("<")      // If only < exists, first < last
    else println("=")                 // If neither exists, all equal
  }
}


// https://github.com/VaHiX/CodeForces/