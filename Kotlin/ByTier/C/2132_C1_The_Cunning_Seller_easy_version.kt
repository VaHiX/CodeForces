// Problem: CF 2132 C1 - The Cunning Seller (easy version)
// https://codeforces.com/contest/2132/problem/C1

/*
 * Problem: C1. The Cunning Seller (easy version)
 *
 * Purpose:
 *   Given a number of watermelons 'n' to buy, determine the minimum cost
 *   to purchase exactly 'n' watermelons using deals where each deal
 *   allows buying 3^x watermelons for 3^(x+1) + x*3^(x-1) coins.
 *   The goal is to minimize the total number of deals used and thereby minimize cost.
 *
 * Algorithms/Techniques:
 *   - Greedy approach: For each step, find the largest deal (3^x) that fits into remaining needed watermelons.
 *   - Precompute powers of 3 for efficiency.
 *   - Use binary search logic to locate the appropriate power of 3.
 *
 * Time Complexity:
 *   O(log n) per test case, due to repeated logarithmic searches for valid deal sizes.
 *   Since there can be up to 10^4 test cases and max n is 10^9, total is around 40*10^6 operations which is acceptable.
 *
 * Space Complexity:
 *   O(1) - only a few variables used regardless of input size.
 */

fun threePow(x: Int): Long {
    var ans = 1L;         // Initialize result to 1 (3^0 = 1)
    repeat(x) {           // Multiply by 3 x times
        ans *= 3;
    }
    return ans;
}

fun costOfPow(x: Int): Long {
    return threePow(x + 1) + x * threePow(x - 1);  // Return cost of a deal for power x
}

fun main() {
    val T = readln().toInt();         // Read number of test cases
    repeat(T) {
        var toBuy = readln().toLong();     // Current amount of watermelons still to buy
        var totalPaid = 0L;                // Total coins spent so far
        
        while (toBuy != 0L) {              // While not all watermelons are bought yet
            var curPow = 0;                // Current power of 3 we're considering
            
            while (threePow(curPow + 1) <= toBuy) {  // Find the largest valid deal smaller or equal to 'toBuy'
                curPow++;
            }
            
            toBuy -= threePow(curPow);     // Deduct this many watermelons from what is needed
            totalPaid += costOfPow(curPow); // Add cost of chosen deal to total paid
            
        }
        println(totalPaid)              // Output final minimum cost
    }
}


// https://github.com/VaHiX/codeForces/