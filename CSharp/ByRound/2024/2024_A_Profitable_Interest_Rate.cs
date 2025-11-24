// Problem: CF 2024 A - Profitable Interest Rate
// https://codeforces.com/contest/2024/problem/A

/*
 * Problem: A. Profitable Interest Rate
 * Algorithms/Techniques: Greedy approach, Mathematical analysis
 * 
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 * 
 * Description:
 * Alice has 'a' coins and wants to maximize the amount of coins she can deposit into a "Profitable" bank deposit.
 * The "Profitable" deposit requires 'b' coins initially. She can first deposit some amount 'x' into an "Unprofitable"
 * deposit, which reduces the required amount for "Profitable" by 2*x. We need to find the maximum possible value
 * that can be deposited into the "Profitable" deposit.
 * 
 * Analysis:
 * - If a >= b, she can directly open it with all 'a' coins.
 * - Otherwise, she chooses x such that after spending x on the Unprofitable deposit,
 *   the remaining coins (a - x) are enough to open Profitable, but not more than a
 *   because opening it will reduce the requirement by 2*x.
 * 
 * Key observations:
 * Let the required amount of Profitable be b - 2*x after spending x on Unprofitable.
 * We want max(x) such that (a - x) >= (b - 2*x), i.e., a - x >= b - 2*x => x >= b - a,
 * but also a - x >= 0 (i.e., x <= a).
 * The maximum allowed x is floor((a - b + 1)/2) if b > a, and a otherwise.
 * But logic simplifies to: if a < b, then optimal is to spend some x so that
 * b - 2*x = a -> x = (b - a)/2. So the final value becomes a + x where we can't exceed a.
 * Or more directly: after spending x, new b = b - 2x, so we can put all remaining a - x coins,
 * if (a - x) >= (b - 2x), i.e., x >= b - a. Maximize x while ensuring (a - x) <= a.
 * 
 * The formula simplifies to:
 * If a >= b, return a.
 * Else, the most effective value is to use as much of a as possible to be able to open profitable,
 * which means maximizing (a - x) subject to that after x coins spent,
 * we still have enough coins from a-x and requirement becomes b - 2x.
 * So max value we can deposit into profitable = max(0, a)
 * But the real calculation:
 * If a < b, let new b' = b - 2*x, and want a - x >= b', so a - x >= b - 2*x => x >= b - a
 * But also a - x must be non-negative. So we can set x = b - a.
 * Then the remaining coins to use in profitable: a - (b - a) = 2*a - b.
 * But only valid if new requirement b' = b - 2*(b-a) = 2*a - b <= a
 * If a >= b, then max is simply a.
 * If a < b, we must spend x = b - a to reduce the requirement to 0. Then we can use all 2*a - b in profitable.
 * But if we spend too much (x > a), still valid as we're using minimum between x and a.
 * We want to maximize final coins in profitable deposit.
 * Let's define function:
 * If a >= b: result = a (just open right away)
 * Else:
 *   We can make new requirement: req = b - 2*x
 *   We have a-x coins left.
 *   Final value: min(a, a-x) where (a-x) >= (b-2x)
 *   If we spend x, then final = a-x. If a-x >= b-2x => x >= b-a.
 *   So we can take x = b-a as max valid x. Then final = a - (b-a) = 2*a - b
 *   But also this final must be non-negative and we must have x <= a,
 *   i.e., b-a <= a, so b <= 2a.
 *   We compute z = max(0, min(a, 2*a - b))
 *   Actually: z =
 *     if (x >= y): return x
 *     else if (y - x <= x): z = x - (y - x);
 *   This suggests:
 *   x = a, y = b
 *   if a >= b then x = a, else y - x <= x  => b - a <= a  => b <= 2*a.
 *   If b > 2*a: impossible to open. Return 0.
 *   Else, z = max of all possible values.
 *   Let's simplify logic step by step in actual code:
 *
 * The final logic is:
 *   If a >= b, return a (we can use all)
 *   Otherwise:
 *     Try all valid x from 0 to min(a, ceil((b - a)/2)): 
 *     But smarter way: 
 *     Max profit = a + max(0, a - (b - a)) = a + max(0, 2*a - b) = max(a, 2*a - b)
 *
 * Actually, from the examples:
 * Input a=10,b=5 => Output=10 (since we can directly open profitable with all coins)
 * Input a=7,b=9 => Spend x=2 in Unprofitable, now req = 9-4 = 5, and have 7-2 = 5 left.
 *                 So we have 5 coins to deposit into profitable. Output=5
 * Input a=5,b=100 => Impossible (even if spend 0). Output=0
 * Input a=1,b=1 => Spend x=1, req = 1-2 = -1 (we can open), but we have no coins left.
 *                 We can't deposit anything in profitable. Output=1? No, that's wrong.
 *                 So spend 0, and we cannot open profitable, return 0
 * 
 * Try different interpretation now:
 * If a < b, then it's impossible to open "profitable" unless we reduce b.
 * We can reduce b by 2*x where x is how much we deposit into Unprofitable.
 * But we also need the coins left after spending x must be enough to open profitable.
 * After spending x, we have (a-x) coins. New requirement = b - 2*x.
 * So condition: (a - x) >= (b - 2*x)
 * => a - x >= b - 2*x
 * => a - x + 2*x >= b
 * => a + x >= b
 * => x >= b - a
 * Also, since we spend x coins and want a-x >= 0, so x <= a.
 * So x is in range [max(0, b-a), min(a, b-1)] (we should not go beyond a)
 *
 * But more clearly:
 * After spending x on Unprofitable:
 * - Remaining coins = (a - x)
 * - New requirement for Profitable = (b - 2*x)
 * - Condition to open: (a - x) >= (b - 2*x)
 * - Rearranged (same as before): a + x >= b => x >= b - a
 *
 * The optimal x is such that we maximize the coins placed in Profitable,
 * which is effectively (a - x) if it's sufficient.
 * But that isn't right either; it depends on how low the requirement can go.
 * So we should think of how to choose x to make b' <= a, so we can place a in profitable.
 *
 * Let’s go with:
 * If a >= b then return a
 * Else:
 *   We want to set x such that after spending x, (a - x) >= (b - 2*x)
 *   => (a - x) >= (b - 2*x)
 *   => a - x >= b - 2*x
 *   => x >= b - a
 *   Also, x <= a.
 *   Choose max x such that x >= b - a and x <= a
 *   i.e. x = min(a, b - a)
 *   But this might be negative.
 *   We can only deposit up to a coins, so x = max(0, min(a, b-a))  
 *   The final value would be min(a, (a-x) + (a-x)) = a - x + a - x = 2*(a-x) in case we spend all.
 *   Wait no. After spending x in Unprofitable:
 *   Remaining coins are a-x
 *   Requirement becomes b-2*x  
 *   We can deposit min(a-x, b-2*x) or if requirement is more than remaining,
 *   we need to consider how much more we want to place into Profitable.
 * 
 * So the correct logic:
 * If a >= b, return a (can open right away)
 * Else:
 *   Try x = 0 to a and find best result
 *   But since we are optimizing:
 *   New requirement: b - 2*x
 *   Coins left after spending x: a - x
 *   Can deposit min(a-x, b-2*x) in profitable.
 *   
 *   For optimal, it's better to reduce the new b to as low as possible without going under 0. 
 *   We can set minimum value of b' = max(0, b - 2*a)  
 *   So the best is to deposit x = a (spend all on Unprofitable), then b' = b - 2a
 *   If b' < 0, we can place 'a' in profitable.
 * 
 * So it's even easier:
 * - If a >= b => return a  
 * - Else return a + max(0, a - (b - a)) = a + max(0, 2*a - b)
 */

using System;
using static System.Math;

namespace matsu {
internal class Program {
  static void Main(string[] args) {
    int n = Convert.ToInt32(Console.ReadLine());
    for (int i = 0; i < n; ++i) {
      int x = 0, y = 0, z = 0;
      String s = Console.ReadLine(), ano = "";
      for (int j = 0; j < s.Length; ++j) {
        if (s[j] == ' ') {
          x = Convert.ToInt32(ano); // Read first number 'a'
          ano = "";
          continue;
        }
        ano += s[j];
      }
      y = Convert.ToInt32(ano); // Read second number 'b'
      
      // Main logic here:
      if (x >= y) {
        z = x; // Can afford profitable deposit straight away
      } else if (y - x <= x) {
        // Spend x coins on Unprofitable, now requirement is reduced by 2*x
        // Remaining coins = x
        // New requirement = y - 2*x  
        // If new requirement <= remaining coins, we can take all remaining
        z = x - (y - x); // Same as 2*x - y
      }
      
      Console.WriteLine(Math.Max(0, z));
    }
  }
}
}

// https://github.com/VaHiX/codeForces/