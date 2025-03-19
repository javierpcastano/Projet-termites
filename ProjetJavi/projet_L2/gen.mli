val case_occupe : char array array -> int -> int -> bool
(** [case_ocuppe char array array -> int -> int] Reçoit un char array array et vérifie si la case d'indices 'i' 'j' est occupé *)


val grid_init : int -> int  -> char array array 
(** [grid_init int -> int -> int]  Initialise une grille pleine de hauteur [n] et de largeur [m]*)

val generate_norm : int -> int -> int -> unit
(** [generate int -> int -> int]  Fonction qui permet de généré et affiché un labyrinthe random avec les caractères de base dans le terminal (elle utilise la fonction grid_init *) 

val generate_coul : int -> int -> int -> unit
(** [generate int -> int -> int]  Fonction qui permet de généré et affiché un labyrinthe random a couleur dans le terminal (elle utilise la fonction grid_init *) 

