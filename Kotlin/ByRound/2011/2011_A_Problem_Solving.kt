// Problem: CF 2011 A - Problem Solving
// https://codeforces.com/contest/2011/problem/A

/*
 * Problem: Determine Jane's problem-solving skill 'x' based on which problems she can solve.
 * 
 * Approach:
 * - For each test case, we are given a list of difficulties in increasing order, with the last being the hardest.
 * - Since Jane solved all but the last problem, it means that:
 *   - The difficulty of the last problem is greater than x (she couldn't solve it).
 *   - All other problems have difficulty <= x (she could solve them).
 * - So, x must be strictly greater than the difficulty of the second-to-last problem,
 *   and also must be at least as large as the difficulty of the last problem.
 * - If all previous elements are less than or equal to (last element - 1), then that value uniquely defines x.
 * - Otherwise, multiple values of x could work → output "Ambiguous".
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to storing the list of difficulties
 */

fun solve() {
    readln() // Read n (but don't use it)
    val a = readln().split(' ').map(String::toInt) // Read and parse the difficulty array
    
    // Check if all elements except the last one are <= (last element - 1)
    // If so, x = last element - 1 is unique
    println(if (a.dropLast(1).contains(a.last() - 1)) (a.last() - 1).toString() else "Ambiguous")
}

fun main() {
    val t = readln().toInt()
    repeat(t) { solve() }
}


// https://github.com/VaHiX/codeForces/