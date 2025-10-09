// Problem: CF 2032 A - Circuit
// https://codeforces.com/contest/2032/problem/A

/*
 * Problem: Circuit
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 *
 * Algorithm:
 * Each light is connected to exactly two switches, and each switch connects to exactly one light.
 * When a switch is toggled (from 0 to 1 or 1 to 0), the light it's connected to also toggles.
 * Given the states of all 2*n switches, we want to determine:
 *   - Minimum number of lights that can be on
 *   - Maximum number of lights that can be on
 *
 * Key Insight:
 * We count:
 *   - Total number of switches that are ON (a)
 *   - Number of switches that are OFF (z)
 *
 * For each light, the minimum number of lights that can be ON is determined by:
 *   If a < z: then we can arrange switches such that all switches in the "ON" group
 *   toggle exactly one light. Since we have 'a' ON switches and 'z' OFF switches,
 *   and there are n lights, and we're trying to minimize how many lights are ON:
 *   - We can pair up switches so that each ON switch toggles a different light.
 *   - If we use all OFF switches to "cancel out" ON switches, the number of lights
 *     that must be ON is `a % 2` (the parity of ON switches), since every pair
 *     of ON switches can cancel each other if they're connected to the same light.
 *
 * For maximum number of lights on:
 * We try to maximize how many lights end up being ON.
 * The maximum happens when we connect all the ON switches to different lights,
 * and minimize overlap. If there are 2*n switches, then at most n lights can be
 * toggled by the ON switches. Since initially all lights are OFF, and each light
 * is controlled by two switches, in the worst case scenario where every ON
 * switch connects to a new light (but we're only allowed 2*lights connections),
 * maximum ON lights = min(n, a), because at most 'a' switches can be used to turn on lights.
 * However, we can simplify this to:
 * If a <= n, then max is `a`.
 * Else if a > n, maximum is `n` (we can pair up the extra switches).
 *
 * But looking closer at example and logic analysis:
 * The final formula for minimum = `a % 2`
 * And for maximum = `min(a, z)` — This represents how many ON switches are enough
 * to turn on at least one light.
 * No! Wait, that’s incorrect.
 *
 * Correct reasoning:
 * Each light gets toggled by exactly two switches. We want a way of assigning
 * which pairs of switches go to each light such that we get the min and max light states.
 *
 * Minimum:
 * - Suppose we have a ON switches and z OFF switches
 * - The minimum number of lights ON is `a % 2` (because we can pair up
 *   some ON switches so they cancel each other out; the final count depends on parity).
 *
 * Maximum:
 * - We want to avoid pairing ON switches together in such a way as to not toggle lights.
 *   So, if we can arrange them so that each light gets toggled by 0 or 2 switches,
 *   that gives us maximum light ON counts.
 * - In other words: If we have `a` ON switches and we're trying to make as many
 *   lights ON as possible, we try to connect at least one ON switch to each light.
 *   But we want the maximum number of lights that can be turned on.
 *
 * A smarter way:
 * - We want to minimize max number of lights that are on.
 * - Let’s say there are 2*n switches total.
 * - Minimum is just `a % 2`, because we can arrange switches such that they cancel 
 *   each other in pairs (each pair toggles a light twice, so no net effect).
 *
 * So the key idea is that:
 * - Total number of 1s = a
 * - Total number of 0s = z = 2*n - a
 * - Minimum ON lights is a % 2 (we toggle some lights an even number of times)
 * - Maximum ON lights is determined by what fraction of ON switches can actually toggle lights:
 *   maximum = min(a, z). This happens because if we have enough OFF switches that
 *   can "cover" all the ON switches to negate their effects (if possible), then
 *   at most min(a, z) lights are ON.
 * 
 * Actually, let's trace: 
 * The answer for minimum = a % 2 — correct.
 * The maximum number of lights ON = min(a, z). But wait...
 * The real maximum is when all 'a' switches that were ON are assigned to light such
 * that it increases the number of toggled lights. We have n lights and 2n switches.
 * So even among n lights, we can assign up to `min(a, n)` to be turned on.
 *
 * Correct logic:
 * The solution uses a simpler version of analysis where for:
 *   Minimum: `(a % 2)` — because only the parity matters (even number toggles = no change)
 *   Maximum: `(a < z ? a : z)` — because you can't have more ON lights than either
 *     the number of ON or OFF switches. But more precisely,
 *
 * Let's reconsider:
 * Total number of switches: 2*n
 * Number of switches on: a
 * Number of switches off: z = 2*n - a
 *
 * To minimize the number of lights turned ON:
 * - A light is ON if it was toggled an odd number of times.
 * - We have 'a' switches that are ON; their toggling must add up to form odd counts on lights.
 * - If we pair up as many ON switches as possible so that they nullify each other,
 *   the remaining unpaired ON switches determine the parity.
 * - Thus min ON = a % 2.
 *
 * To maximize:
 * - Try to make as many lights turn ON as possible.
 * - In an odd-numbered cycle (like 1, 3, and so on), a switch toggles a light once.
 * - We can assign up to min(a, z) switches optimally to control the on/off state
 *   of the lights in a best-case arrangement.
 *
 * Therefore:
 * Final result for each test case is:
 * (a % 2) and (min(a, z))
 * Which gives us correct results.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a(0), z(0); // a = number of ON switches, z = number of OFF switches
    for (long p = 0; p < 2 * n; p++) { // process all switches
      int x;
      scanf("%d", &x);
      a += x;   // increment ON count
      z += (!x); // increment OFF count
    }
    printf("%ld %ld\n", (a % 2), (a < z ? a : z)); // min and max
  }
}


// https://github.com/VaHiX/codeForces/