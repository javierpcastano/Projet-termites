(* open Solve  *)

let rec dump_file fich =
  try 
    let line = input_line fich in
    Printf.printf "%s\n" line;
    dump_file fich
  with
  | End_of_file -> close_in fich
;;

let read_and_print fichier = 
    dump_file fichier
;;

let display_help_message () = 
    Printf.printf "\n Pour executer le programme vous avez les options suivantes :\n\n";
    Printf.printf "./maze.exe print <fichier.laby> : lit le labyrinthe se trouvant dans\
    le fichier \"fichier.laby\" et l’affiche dans la console\n\n";
    
    Printf.printf "./maze.exe solve <fichier.laby> : lit le labyrinthe se trouvant dans\
    le fichier \"fichier.laby\" et l’affiche dans la console en mettant en évidence le chemin\
    du départ vers l’arrivée\n\n";
    
    Printf.printf "./maze.exe random <n> <m> [r] : génère un labyrinthe (sans couleurs, i.e. caractères de base) aléatoire de hauteur\
    n et de largeur m, utilisant éventuellement l’entier positif r comme graine initiale pour\
    le générateur de nombres aléatoires.\n\n";
    
    Printf.printf "./maze.exe random coul <n> <m> [r] : génère un labyrinthe (avec l'affichage amélioré) aléatoire de hauteur\
    n et de largeur m, utilisant éventuellement l’entier positif r comme graine initiale pour\
    le générateur de nombres aléatoires.\n\n"
;;

let () =
    match Array.to_list Sys.argv with
    | [ _; "--help" ] -> display_help_message ()
    | [ _; "print"; fichier ] -> read_and_print (open_in fichier)
    | [ _; "solve"; fichier ] -> Solve.solve fichier
    | [ _; "solve"; "coul"; fichier ] -> Solve.solve_coul fichier
    | [ _; "random"; n; m; seed] -> Gen.generate_norm (int_of_string n) (int_of_string m) (int_of_string seed)
    | [ _; "random"; "coul"; n; m; seed] -> Gen.generate_coul (int_of_string n) (int_of_string m) (int_of_string seed)
    | _ -> failwith "ligne de commande invalide ; essaye :\"./maze.exe --help\"" 
;; 