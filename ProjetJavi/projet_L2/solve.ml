(* solve.ml *)
open Grid
open Affichage

let print_chemin chemin = 
  Printf.printf "Estamos dentro\n";
  List.iter(fun (i, j) -> Printf.printf "(%d, %d)\n" i j ) chemin

 let rec remove_last = function
  | [] -> []
  | [x] -> []  (* Cas où il n'y a qu'un élément dans la liste *)
  | hd :: tl -> hd :: remove_last tl
  
let rec remove_first_element = function
  | [] -> []
  | _ :: rest -> rest
  
let remove_first_and_last lst =
  match List.rev lst with
  | [] -> []
  | _ :: tl -> List.rev (List.tl tl)

  
let is_valid_move labyrinthe i j =
  (* i > 0 && i < (Array.length labyrinthe - 1) && j > 0 && j < (Array.length labyrinthe.(0) - 1) && labyrinthe.(i).(j) <> '|' && labyrinthe.(i).(j) <> '-'  *)
  labyrinthe.(i).(j) = ' ' || labyrinthe.(i).(j) = 'E' || labyrinthe.(i).(j) = 'S'

let is_exit labyrinthe i j =
  labyrinthe.(i).(j) = 'E'

let is_start labyrinthe i j =
  labyrinthe.(i).(j) = 'S'

let est_libre laby i j =
  laby.(i).(j) = ' ' || laby.(i).(j) = 'E' || laby.(i).(j) = 'S' 

let case_visite labyrinthe i j =
  labyrinthe.(i).(j) = '*'
  
let voisin_libre laby i j = 
  is_valid_move laby (i-1) j || is_valid_move laby (i+1) j || is_valid_move laby i (j-1) || is_valid_move laby i (j+1)

(*
let rec solvRec labyrinthe visit chemin i j =
  Printf.printf "(%d, %d, %b)\n" i j visit.(i).(j);
  if i > 0 && i < Array.length labyrinthe - 1 && j > 0 && j < Array.length labyrinthe.(0) - 1 then 
    if is_exit labyrinthe i j then begin
      Printf.printf "ok1\n";
      (true, chemin)
    end
    else if case_visite labyrinthe i j && not (voisin_libre labyrinthe i j) then begin 
      Printf.printf "ok2\n";
      (false, chemin)
    end
    else if voisin_libre labyrinthe i j && not (visit.(i).(j)) then begin
      Printf.printf "ok3\n";
      let chemin = (i, j)::chemin in
      (* if labyrinthe.(i).(j) = ' ' then  labyrinthe.(i).(j) <- '*'; Pour ne pas sauter des murs*)
      if not (is_valid_move labyrinthe i j) then 
        (false, chemin)
      else begin
        visit.(i).(j) <- true;
      
        let directions = [|(-1, 0); (1, 0); (0, -1); (0, 1)|] in
        let rec find_exit idx solu =
          if idx = Array.length directions then
            (false, chemin)
          else
            let (di, dj) = directions.(idx) in
            let ni, nj = i + di, j + dj in
            let exit_found, new_chemin = solvRec labyrinthe visit ((ni, nj) :: solu) ni nj in
            if exit_found then
              (true, new_chemin)
            else
              find_exit (idx + 1) new_chemin
        in
        find_exit 0 chemin
      end
    end else
      (false, chemin) (* Cierra 39 *)
    else
      (false, chemin) (* Cierra 31 *)
*)


let rec solvRec labyrinthe visit chemin i j =
(*     Printf.printf "(%d, %d, %b)\n" i j visit.(i).(j); *)
  if i > 0 && i < Array.length labyrinthe - 1 && j > 0 && j < Array.length labyrinthe.(0) - 1 then 
    if is_exit labyrinthe i j then begin
(*           Printf.printf "ok1\n"; *)
          (true, chemin)
      end
    else if case_visite labyrinthe i j then begin (* Si la case est visitÃ©e *)
(*           Printf.printf "ok2\n"; *)
          (false, chemin)
          end
    else if est_libre labyrinthe i j && voisin_libre labyrinthe i j && not (visit.(i).(j)) then begin (* Si la case est virgen y puede moverse *)
(*           Printf.printf "ok3\n"; *)
          let chemin = (i, j)::chemin in (*No martin*)
         (* if labyrinthe.(i).(j) = ' ' then  labyrinthe.(i).(j) <- '*'; Pour ne pas sauter des murs No martin *)
      visit.(i).(j) <- true;
      
      let directions = [|(-1, 0); (1, 0); (0, -1); (0, 1)|] in
      let rec find_exit idx solu =
        if idx = Array.length directions then
          (false, chemin)
        else
          let (di, dj) = directions.(idx) in
(*           let ni, nj = i + di, j + dj in *)
          let exit_found, new_chemin = solvRec labyrinthe visit ((i, j) :: solu) (i + di) (j + dj) in
          if exit_found then
            (true, new_chemin)
          else
            find_exit (idx + 1) solu
      in
      find_exit 0 chemin
    end else
      (false, chemin) (*Cierra 39*)
  else
    (false, chemin) (*Cierra 31*)


let solve_coul fich =
  let c_in = open_in fich in
  let labyrinthe = file_to_2Darray c_in in
  close_in c_in;

  let visitees = Array.make_matrix (Array.length labyrinthe) (Array.length labyrinthe.(0)) false in

  let rec find_start i j =
    if i < Array.length labyrinthe then
      if j < Array.length labyrinthe.(0) then
        if is_start labyrinthe i j then
          (i, j)
        else if j + 1 < Array.length labyrinthe.(0) then
          find_start i (j + 1)
        else
          find_start (i + 1) 0
      else
        find_start (i + 1) 0
    else
      failwith "Start not found"
  in

  let start_row, start_col = find_start 0 0 in
  visitees.(start_row).(start_col) <- false;

(*   Printf.printf "lig : %d, col: %d\n" start_row start_col; *)

  let exit_found, chemin = solvRec labyrinthe visitees [] start_row start_col in
  (* Stocker les positions du chemin correct *)
  let nouv_chemin = remove_first_and_last chemin in

(*   print_chemin chemin; *)

  (* Modifier le labyrinthe uniquement pour les positions valides du chemin après l'exploration *)
  List.iter (fun (i, j) -> (*if is_valid_move labyrinthe i j then*) labyrinthe.(i).(j) <- '*') nouv_chemin;
  print_ameliore_labyrinthe labyrinthe;

  if exit_found then
    Printf.printf "La sortie a été trouvée.\n"
  else
    Printf.printf "Aucun chemin vers la sortie n'a été trouvé.\n"
;;

let solve fich =
  let c_in = open_in fich in
  let labyrinthe = file_to_2Darray c_in in
  close_in c_in;

  let visitees = Array.make_matrix (Array.length labyrinthe) (Array.length labyrinthe.(0)) false in

  let rec find_start i j =
    if i < Array.length labyrinthe then
      if j < Array.length labyrinthe.(0) then
        if is_start labyrinthe i j then
          (i, j)
        else if j + 1 < Array.length labyrinthe.(0) then
          find_start i (j + 1)
        else
          find_start (i + 1) 0
      else
        find_start (i + 1) 0
    else
      failwith "Start not found"
  in

  let start_row, start_col = find_start 0 0 in
  visitees.(start_row).(start_col) <- false;

(*   Printf.printf "lig : %d, col: %d\n" start_row start_col; *)

  let exit_found, chemin = solvRec labyrinthe visitees [] start_row start_col in
  (* Stocker les positions du chemin correct *)
  let nouv_chemin = remove_first_and_last chemin in

(*   print_chemin chemin; *)

  (* Modifier le labyrinthe uniquement pour les positions valides du chemin après l'exploration *)
  List.iter (fun (i, j) -> (*if is_valid_move labyrinthe i j then*) labyrinthe.(i).(j) <- '*') nouv_chemin;
  print_labyrinthe labyrinthe;

  if exit_found then
    Printf.printf "La sortie a été trouvée.\n"
  else
    Printf.printf "Aucun chemin vers la sortie n'a été trouvé.\n"
;;

(* solve "test/maze_6x6.laby";; *)





(*******************

PARTIE INUTILE 

****************)

(*let rec resoudre_labyrinthe labyrinthe i j =
  let n = Array.length labyrinthe in
  let m = Array.length labyrinthe.(0) in

  let est_sortie i j = labyrinthe.(i).(j) = 'E' in
  let est_debut i j = labyrinthe.(i).(j) = 'S' in
  let marquer_visite i j = labyrinthe.(i).(j) <- 'x' in

  if est_sortie i j then
    true
  else if labyrinthe.(i).(j) = 'x' then
    false
  else begin
    marquer_visite i j;

    let voisines i j =
      [(i - 1, j); (i + 1, j); (i, j - 1); (i, j + 1)]
      |> List.filter (fun (ni, nj) -> ni > 0 && ni < n && nj > 0 && nj < m)
    in

    let rec explore_voisines = function
      | [] -> false
      | (ni, nj) :: rest ->
        if resoudre_labyrinthe labyrinthe ni nj then
          true
        else
          explore_voisines rest
    in

    explore_voisines (voisines i j)
  end

;;
  (*Résolution du labyrinthe *)
 
let solve fich = 
  let c_in = open_in fich in
  let labyrinthe = file_to_2Darray c_in in
  close_in c_in;
  
  let rec find_start i j =
    if i < Array.length labyrinthe then
      if j < Array.length labyrinthe.(0) then
        if is_start labyrinthe i j then
          (i, j)
        else if j + 1 < Array.length labyrinthe.(0) then
          find_start i (j + 1)
        else
          find_start (i + 1) 0
      else
        find_start (i + 1) 0
    else
      failwith "Start not found"
  in

  let i, j = find_start 0 0 in

  if resoudre_labyrinthe labyrinthe i j then begin
    Printf.printf "Labyrinthe résolu!\n";
    (* Affichage du labyrinthe résolu *)
    print_labyrinthe labyrinthe;
  end else
    Printf.printf "Impossible de résoudre le labyrinthe.\n"
;;

solve "test/maze_6x6.laby";;
*)


