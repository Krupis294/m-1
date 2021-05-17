<?php

  # Adresa, Uzivatel, Heslo, Databaze
  $spojeni = mysqli_connect("localhost", "root", "", "pokemon");
  
  if ($spojeni == null) {
    die("Spojeni selhalo!");
  } else {
    # echo "Spojeno";
  }

?>
