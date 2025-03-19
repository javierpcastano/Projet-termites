(* solve.mli *)


val solve : string -> unit
(** [solve : string -> unit] Tente de résoudre le labyrinthe donné.
    Affiche le labyrinthe (avec les caractères de base ) avec le chemin trouvé s'il existe, sinon affiche un message indiquant
    qu'aucun chemin n'a été trouvé. *)

val solve_coul : string -> unit
(** [solve_coul : string -> unit] tente de résoudre le labyrinthe donné.
    Affiche le labyrinthe, avec l'affichage amélioré, du chemin trouvé s'il existe, sinon affiche un message indiquant
    qu'aucun chemin n'a été trouvé. *)
