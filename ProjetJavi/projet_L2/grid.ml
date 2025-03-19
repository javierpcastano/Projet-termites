(* open Random  *)

type grille = char array array

(* let is_valid_char c =
  match c with
  | 'S' | 'E' | '~' | '+' | '-' | '|' | ' ' -> true
  | _ -> false *)
  
  
let file_to_2Darray c_in =
  let rec loop acc =
    try
      let s = input_line c_in in
      loop (s :: acc)
    with
      End_of_file -> List.rev acc
  in
  let lines = loop [] in
  let char_arrays =
    List.map (fun line -> Array.init (String.length line) (fun i -> line.[i])) lines
  in
  Array.of_list char_arrays

let print_2Darray fich =
  let c_in = open_in fich in
  let maze_array = file_to_2Darray c_in in close_in c_in;
  Array.iter (fun row -> Array.iter (fun cell -> print_char cell) row; print_newline ()) maze_array
;;

print_2Darray "test/maze_2x1.laby";;

let verify_is_ok lab = 
    let rec loop acc1 acc2 cptS cptE =
        let height = Array.length lab in
        let long = Array.length lab.(0) in
        
        if (long != Array.length lab.(acc1)) then failwith "toutes les lignes ne sont pas de même longueur" (* On vérifie que toutes les lignes soient de même longueur*)
        
        else if (acc1 mod 2 = 0 && acc2 mod 2 = 0 && lab.(acc1).(acc2) <> '+' ) then failwith "Erreur dans un +" (* On vérifie que tous le '+' soient bien placés*)
        
        else if (acc1 mod 2 = 1 && (acc2 = 0 || acc2 = long - 1) && lab.(acc1).(acc2) <> '|' ) then failwith "Manque un mur du côté" (* On vérifie que tous les murs verticales des côtés soient placés*)
        else if (acc1 mod 2 = 1 && acc2 mod 2 = 0 && (lab.(acc1).(acc2) <> '|' && lab.(acc1).(acc2) <> ' ')  ) then failwith "Erreur a la place d'un mur vertivale ou espace intérieur" (*On vérifie que tous les murs verticales de l'intérieur soient soit des murs verticales soit des espaces *)
        
        else if ((acc1 = 0 || acc1 = height - 1) && acc2 mod 2 = 1 && lab.(acc1).(acc2) <> '-' ) then failwith "le labyriranthe n'est pas bien fermé" (* On vérifie que la première et dernière ligne du labyrinthe soient bien complètes de moins*)
        else if (acc1 mod 2 = 0 && acc2 mod 2 = 1 && (lab.(acc1).(acc2) <> '-' && lab.(acc1).(acc2) <> ' ') ) then failwith "Erreur a la place d'un mur horizontale u espace intérieur" (*On vérifie que tous les murs horizontales de l'intérieur soient soit des murs horizontales soit des espaces *)
        
        else if (acc1 mod 2 = 1 && acc2 mod 2 = 1 && (lab.(acc1).(acc2) <> 'E' && lab.(acc1).(acc2) <> 'S' && lab.(acc1).(acc2) <> ' ') ) then failwith "Erreur a la place d'un 'S', 'E' ou ' '" (*On vérifie que les seules valeurs a l'intérieur des cases soient soit un E soit un S soit un espace*)
        
        else if (acc2 < long - 1) then
            match lab.(acc1).(acc2) with
                | 'S' -> loop acc1 (acc2+1) (cptS+1) cptE    (*Ici on compte nombre le nombre de Sorties et Entrées qu'il y a dans le labyrinthe*)
                | 'E' -> loop acc1 (acc2+1) cptS (cptE+1)
                | _ -> loop acc1 (acc2+1) cptS cptE
        else if (acc1 < height - 1) then loop (acc1+1) 0 cptS cptE
        
        else if cptS <> 1 then failwith "Il devrait y avoir exactement un lieu de sortie" (*On vérifie qu'il y a exactement un lieu de sortie*)
        else if cptE <> 1 then failwith "Il devrait y avoir exactement un lieu d'arrivée" (*On vérifie qu'il y a exactement un lieu d'arrivée*)
        
        
 
    in
    loop 0 0 0 0;
    Printf.printf "Le labyrinthe est correct\n"



let maze_test = file_to_2Darray (open_in "test/maze_3x2_faux.laby");;
let maze_test1 = file_to_2Darray (open_in "test/maze_3x2_faux1.laby");;
let maze_test2 = file_to_2Darray (open_in "test/maze_3x2_faux2.laby");;
let maze_test3 = file_to_2Darray (open_in "test/maze_3x2_faux3.laby");;
let maze_test4 = file_to_2Darray (open_in "test/maze_3x2_faux4.laby");;
let maze_test5 = file_to_2Darray (open_in "test/maze_3x2_faux5.laby");;

(*verify_is_ok maze_test;;
verify_is_ok maze_test1;;
verify_is_ok maze_test2;;
verify_is_ok maze_test3;;
verify_is_ok maze_test4;;
verify_is_ok maze_test5;;*)

