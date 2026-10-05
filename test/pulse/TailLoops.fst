module TailLoops

module U32 = FStar.UInt32

(* A leading exit test, with another return in the loop body. *)
let rec search (n key: U32.t): Tot U32.t (decreases U32.v n) =
  if n = 0ul then 0ul
  else if n = key then n
  else search (U32.sub n 1ul) key

(* The terminating branch may also be the else branch. *)
let rec countdown (n: U32.t): Tot U32.t (decreases U32.v n) =
  if n <> 0ul then countdown (U32.sub n 1ul)
  else n

(* Keep simultaneous assignment of recursive arguments intact. *)
let rec swap (n x y: U32.t): Tot U32.t (decreases U32.v n) =
  if n = 0ul then x
  else swap (U32.sub n 1ul) y x

(* Unit-valued returns use the same guard transformation. *)
let rec countdown_unit (n: U32.t): Div unit =
  if n = 0ul then ()
  else countdown_unit (U32.sub n 1ul)
