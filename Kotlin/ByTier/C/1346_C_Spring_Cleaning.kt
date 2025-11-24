// Problem: CF 1346 C - Spring Cleaning
// https://codeforces.com/contest/1346/problem/C

/*
 * Problem: C. Spring Cleaning
 *
 * Purpose: Find minimum time to make all bookshelves have at most k books,
 * using two operations:
 * 1. Remove all books from one shelf (cost x seconds)
 * 2. Evenly distribute all books among shelves (cost y seconds)
 *
 * Algorithms/Techniques:
 * - Greedy approach with sorting and prefix processing
 * - Simulation of removing shelves and checking feasibility
 * - Even distribution via ceiling division for average
 *
 * Time Complexity: O(n log n + n^2) where n is number of bookshelves.
 *   Sorting takes O(n log n), and the while loop inside solve() can go up to O(n^2) in worst case.
 *
 * Space Complexity: O(n) for storing the list of books
 */
import java.io.BufferedReader
import java.io.InputStreamReader

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val output = StringBuilder()
    val t = br.readLine().toInt()
    repeat(t) { output.append(solve(br)) }
    print(output)
}

fun solve(br: BufferedReader): String {
    val (n, k, x, y) = br.readLine().split(" ").map { it.toLong() }
    val a = br.readLine().split(" ").map { it.toLong() }.toMutableList()
    a.sort() // Sort to process from largest to smallest
    var sum = a.sum()
    var ans = 10_000_000_000L // Initialize with large value
    val avg = (sum + n - 1) / n // Calculate ceiling average for even distribution
    
    // If average is already within limit, check if any shelf exceeds k
    if (avg <= k) {
        if (a.last() > k) {
            ans = y // Only use second operation if needed
        } else {
            ans = 0 // No operations needed
        }
    }
    
    var cnt = 0L
    while (a.isNotEmpty()) {
        val last = a.last()
        sum -= last
        a.removeAt(a.lastIndex)
        cnt++
        
        // Check if removing this shelf makes average exceed k
        if ((sum + n - 1) / n > k) {
            continue // Skip this removal as it would still be invalid
        }
        
        val cur = x * cnt // Cost of removing cnt shelves
        val additionalCost = if (a.isNotEmpty() && a.last() > k) y else 0L // Cost of final distribution
        
        ans = minOf(ans, cur + additionalCost)
    }
    
    return "$ans\n"
}


// https://github.com/VaHiX/codeForces/