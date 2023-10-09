(* Copyright (c) INRIA and Microsoft Corporation. All rights reserved. *)
(* Licensed under the Apache 2.0 License. *)

type calling_convention =
  | StdCall
  | CDecl
  | FastCall
  [@@deriving yojson,show]

type lifetime =
  | Eternal
  | Stack
  | Heap
  [@@deriving yojson,show]

type forward_kind =
  | FUnion
  | FStruct
  [@@deriving yojson,show]

type flag =
  | Private
      (** An F* private qualifier. *)
  | WipeBody
      (** DEPRECATED. Left there for compatibility with previous ASTs. *)
  | Inline
      (** User demanded a C inline keyword *)
  | Substitute
      (** DEPRECATED. User used [@ Substitute ] -- function inlined at call-site, but not
       * necessarily removed. Deprecated in favor of using inline_for_extraction
       * at the F* level. *)
  | GcType
      (** Automatic insertion of pointers because this type will be collected
       * by a conservative garbage collector. *)
  | Comment of string
      (** The function contained a comment. *)
  | MustDisappear
      (** This function *must* disappear, i.e. it shall be inlined at call-site
       * and its definition shall be removed entirely. Used for Ghost and
       * StackInline functions. *)
  | Const of string
      (** DEPRECATED. Identify a parameter by name, to be marked as const. Deprecated in
       * favor of LowStar.ConstBuffer. *)
  | Prologue of string
      (** Verbatim C code, inserted before. *)
  | Epilogue of string
      (** Verbatim C code, inserted after. *)
  | AbstractStruct
      (** Struct type only revealed as a forward declaration in the interface *)
  | IfDef
      (** Branches over this variable are compiled as #ifdefs *)
  | Macro
      (** Definition compiled as a macro *)
  | Deprecated of string
      (** Currently behind a macro, GCC only *)
  | NoInline
  | Internal
      (** After reachability analysis, means that a prototype will be generated
          in an internal header. Not generated by F*. *)
  | AutoGenerated
      (** Allows eliminating type abbreviations that originally stem from
          auto-generated names. *)
  | MaybeUnused
  [@@deriving yojson,show]
