open Affichage


let case_occupe laby i j = 
    if laby.(i).(j) <> ' ' then 
        true
    else 
        false
;;

 (*AQUI PROBLEMA FUE ELEGIR UNA CASILLA VALIDA PARA 'S' O 'E' *)

let grid_init n m =
  if (n + m) < 3 || n <= 0 || m <= 0 then failwith "Dimensions invalides";
  let ligne_complete () =
    Array.init (2 * m + 1) (fun i -> if i mod 2 = 0 then '+' else '-')
  in
  let ligne_vide () =
    Array.init (2 * m + 1) (fun i -> if i mod 2 = 0 then '|' else ' ')
  in
  let creation_lab () =
    Array.init (2 * n + 1) (fun i ->
      if i mod 2 = 0 then
        ligne_complete ()
      else
        ligne_vide ()
    )
  in
  creation_lab ()
;;


let rec melange_array arr =
  let len = Array.length arr in
  if len <= 1 then
    ()
  else begin
    let dernier_index = len - 1 in
    let random_index = Random.int len in

    (* Change le dernier élément avec un autre au "hasard" *)
    let tmp = arr.(dernier_index) in
    arr.(dernier_index) <- arr.(random_index);
    arr.(random_index) <- tmp;

    (* Mélange les éléments restants *)
    melange_array (Array.sub arr 0 dernier_index)
  end
;;


let generate_norm n m seed =
  let labyrinthe = grid_init n m in
  Random.init seed;

  let case_visite i j =
    labyrinthe.(i).(j) = '*'
  in

  let rec case_valides () =
    let init_ligne = Random.int (n * 2 + 1) in
    let init_col = Random.int (m * 2 + 1) in
    let sortie_ligne = Random.int (n * 2 + 1) in
    let sortie_col = Random.int (m * 2 + 1) in

    if init_ligne mod 2 = 1 && init_col mod 2 = 1 &&
       sortie_ligne mod 2 = 1 && sortie_col mod 2 = 1 &&
       (init_ligne, init_col) <> (sortie_ligne, sortie_col) then
      (init_ligne, init_col, sortie_ligne, sortie_col)
    else
      case_valides ()
  in

  let (init_ligne, init_col, sortie_ligne, sortie_col) = case_valides () in

  let rec explore i j =
    if i >= 0 && i < 2 * n + 1 && j >= 0 && j < 2 * m + 1 && not (case_visite i j) then
      begin
        labyrinthe.(i).(j) <- '*';

        let directions = [|(-2, 0); (2, 0); (0, -2); (0, 2)|] in
        let directions_aleat = Array.to_list directions |> List.sort (fun _ _ -> Random.int 3 - 1) |> Array.of_list in

        Array.iter (fun (di, dj) ->
          let ni = i + di in
          let nj = j + dj in
          if ni >= 0 && ni < 2 * n + 1 && nj >= 0 && nj < 2 * m + 1 && not (case_visite ni nj) then
            begin
              labyrinthe.(i + di / 2).(j + dj / 2) <- ' ';
              explore ni nj
            end
        ) directions_aleat
      end
  in

  explore init_ligne init_col;

  labyrinthe.(sortie_ligne).(sortie_col) <- 'S';
  labyrinthe.(init_ligne).(init_col) <- 'E';

  (* Affichage du labyrinthe *)
  print_labyrinthe labyrinthe;
  ()
;;


let generate_coul n m seed =
  let labyrinthe = grid_init n m in
  Random.init seed;

  let case_visite i j =
    labyrinthe.(i).(j) = '*'
  in

  let rec case_valides () =
    let init_ligne = Random.int (n * 2 + 1) in
    let init_col = Random.int (m * 2 + 1) in
    let sortie_ligne = Random.int (n * 2 + 1) in
    let sortie_col = Random.int (m * 2 + 1) in

    if init_ligne mod 2 = 1 && init_col mod 2 = 1 &&
       sortie_ligne mod 2 = 1 && sortie_col mod 2 = 1 &&
       (init_ligne, init_col) <> (sortie_ligne, sortie_col) then
      (init_ligne, init_col, sortie_ligne, sortie_col)
    else
      case_valides ()
  in

  let (init_ligne, init_col, sortie_ligne, sortie_col) = case_valides () in

  let rec explore i j =
    if i >= 0 && i < 2 * n + 1 && j >= 0 && j < 2 * m + 1 && not (case_visite i j) then
      begin
        labyrinthe.(i).(j) <- '*';

        let directions = [|(-2, 0); (2, 0); (0, -2); (0, 2)|] in
        let directions_aleat = Array.to_list directions |> List.sort (fun _ _ -> Random.int 3 - 1) |> Array.of_list in

        Array.iter (fun (di, dj) ->
          let ni = i + di in
          let nj = j + dj in
          if ni >= 0 && ni < 2 * n + 1 && nj >= 0 && nj < 2 * m + 1 && not (case_visite ni nj) then
            begin
              labyrinthe.(i + di / 2).(j + dj / 2) <- ' ';
              explore ni nj
            end
        ) directions_aleat
      end
  in

  explore init_ligne init_col;

  labyrinthe.(sortie_ligne).(sortie_col) <- 'E';
  labyrinthe.(init_ligne).(init_col) <- 'S';

  (* Affichage du labyrinthe *)
  print_ameliore_labyrinthe labyrinthe;
  ()
;;


