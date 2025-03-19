val case_occupe : char array array -> int -> int -> bool
(** [case_ocuppe char array array -> int -> int] Reçoit un char array array et vérifie si la case d'indices 'i' 'j' est occupé *)

val grid_init : int -> int  -> char array array 
(** [grid_init int -> int -> int]  Initialise une grille pleine de hauteur [n] et de largeur [m]*)

val generate_norm : int -> int -> int -> unit
(** [generate_norm int -> int -> int]  Utilsant la fonction grid_init du module Grid, lonction permet de généré et affiché un labyrinthe (de taille [n] x [m]) aléatoire a partir d'une "seed" avec les caractères de base dans le terminal*) 

val generate_coul : int -> int -> int -> unit
(** [generate_coul int -> int -> int]  Utilsant la fonction grid_init du module Grid, la fonction permet de généré et affiché un labyrinthe (de taille [n] x [m]) aléatoire a partir d'une "seed" a couleur dans le terminal *) 

