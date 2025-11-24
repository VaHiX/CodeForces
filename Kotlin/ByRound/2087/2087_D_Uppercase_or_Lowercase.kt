// Problem: CF 2087 D - Uppercase or Lowercase?
// https://codeforces.com/contest/2087/problem/D

/*
 * Problem: D. Uppercase or Lowercase?
 * Purpose: Find the position of a given handle in a sorted list of handles where it's unknown whether
 *          uppercase letters are considered less than lowercase ones (lexicographical ordering).
 *          Uses binary search with a custom comparison function to determine the correct ordering.
 *
 * Algorithm: Binary Search on Answer
 * Time Complexity: O(log n) queries, each query is O(1)
 * Space Complexity: O(1) - only using a few variables for tracking
 */
fun query(x: Int): String {
    println("? ${x + 1}") // Query the database for handle at index x+1 (1-based)
    System.out.flush()   // Ensure output is sent immediately
    return readln()
}

fun lower(a: String, b: String, rev: Boolean): Boolean {
    val a_ = a[0].isLowerCase()  // Check if first char of 'a' is lowercase
    val b_ = b[0].isLowerCase()  // Check if first char of 'b' is lowercase
    if (a_ == b_) {
        return a <= b // If both are same case, compare lexicographically directly
    }
    return a_ == rev // If different case, use the 'rev' flag to determine which is smaller
}

fun main() {
    val (n_, h) = readln().split(" ")  // Read n and handle h from input
    val n = n_.toInt()
    val rev = query(0)[0].isLowerCase()  // Query first element to determine ordering type ('rev' flag)
    var l = 0         // Left boundary for binary search (0-based)
    var r = n         // Right boundary for binary search
    var mid = (l + r) / 2   // Midpoint used in binary search loop
    
    while (r - l > 1) {     // Continue until only one element remains in range
        if (lower(query(mid), h, rev)) l = mid else r = mid  // Decide which half contains the target
        mid = (l + r) / 2   // Update midpoint for next iteration
    }
    
    println("! ${l + 1}")  // Output final result (1-based index)
}


// https://github.com/VaHiX/codeForces/