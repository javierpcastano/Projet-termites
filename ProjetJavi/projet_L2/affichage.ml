let reset = "\x1b[0m";;

let print_ameliore_labyrinthe labyrinthe =
  let char_to_couleur c = 
    match c with 
    | ' ' | '~' -> Printf.sprintf "\x1b[47m  %s" reset (*Blanc*)
    | '+' | '-' | '|' -> Printf.sprintf "\x1b[40m  %s" reset (*Noir*)
    | 'S' -> Printf.sprintf "\x1b[41m  %s" reset (*Rouge*)
    | 'E' -> Printf.sprintf "\x1b[44m  %s" reset (*Bleu*)
    | '*' -> Printf.sprintf "\x1b[42m  %s" reset (*Vert*)
    | _ -> ""
  in

  Array.iter (fun ligne -> Array.iter (fun case -> Printf.printf "%s" (char_to_couleur case)) ligne; print_newline ()) labyrinthe
;;


let print_labyrinthe labyrinthe =
  Array.iter (fun ligne -> Array.iter (fun case -> if case = '*' then Printf.printf "*" else print_char case) ligne; print_newline ()) labyrinthe
;;