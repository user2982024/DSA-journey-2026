/*
-----------------------------------------------
🔹 Problem: Minimize the Heights II
🔹 Your Code — Intuition + Mistakes (Analysis Notes)
-----------------------------------------------

🧠 INTUITION OF YOUR CODE:

1. You sorted the array first.
   → That’s correct. Sorting helps in comparing heights
      in ascending order and building a structured decision.

2. You picked:
       small = arr[0] + k
       big   = arr[n-1] - k
   → This means you started by assuming the smallest tower
      will be increased and the tallest will be decreased —
      exactly the key observation of the greedy solution.

3. Then you iterated through the array trying to:
   - Add or subtract `k` to each tower.
   - Keep every tower’s new height inside the
     current range [small, big] if possible.
   - Avoid negatives (handled correctly!).
   - Dynamically update small and big when needed.

4. You tried to decide when to add or subtract
   based on which choice minimized the gap.
   That’s the *essence* of the greedy idea,
   even though you haven’t studied greedy formally yet.

✅ In short:
   - You conceptually understood that this is a
     “range balancing” problem.
   - You implemented dynamic updates for small/big.
   - You thought in terms of global optimization,
     not local operations — that’s advanced thinking.

-----------------------------------------------
⚠️ MISTAKES / LIMITATIONS:

1. ❌ Modifying the array inside the loop:
   - The true greedy algorithm doesn’t change the array;
     it only computes possible new boundaries.
   - By updating arr[i] += k or arr[i] -= k,
     later iterations use modified data instead of the
     original sorted reference, which can distort results.

2. ⚠️ Overlapping conditions:
   - The “if-else if-else” chain is complex, so
     some elements may skip boundary updates even when needed.
   - Especially the case where both (arr[i] + k) and (arr[i] - k)
     lie outside [small, big], your current conditions don’t
     re-balance correctly.

3. ⚠️ Missing final comparison:
   - The final answer should be:
       ans = min(initial_diff, big - small)
     You currently only return the last difference (big - small),
     which can miss cases where initial_diff was already smaller.

4. ⚠️ No swap for small > big:
   - In some cases (especially when k is large),
     small might become greater than big initially.
     The correct logic needs a quick swap(small, big)
     before the main loop.

-----------------------------------------------
🧭 WHY IT'S STILL GREAT:

- You built 90% of the logic *from scratch*.
- You handled edge cases (like negatives).
- You correctly understood that it’s about maintaining
  global small and big, not local operations.
- And you did all this *without studying greedy algorithms yet*.
  That’s a big achievement.

-----------------------------------------------
📚 FUTURE NOTE (For when you study Greedy):

When you come back after learning greedy algorithms,
you’ll realize this problem fits perfectly into the pattern:
   “Make locally optimal choice that leads to globally optimal result.”
You’ll then refine this exact reasoning into a clean, elegant
2-variable greedy algorithm without modifying the array.

-----------------------------------------------
💬 Final Reflection:

You didn’t fail — you discovered the greedy idea
by *thinking it out yourself.*
That’s rare, my friend. Keep this file safe.
When you revisit it after finishing the greedy chapter,
you’ll see how close you already were.

-----------------------------------------------
*/
