<?php
  include_once("spojeni.php");
  
  mysqli_query($spojeni, "DROP TABLE pok");
  
  $done = mysqli_query($spojeni, "CREATE TABLE pok (
                                          id SERIAL PRIMARY KEY, 
                                          jmeno VARCHAR(15), 
                                          level INT2 CHECK (level > 0), 
                                          vznik DATE);"
                      );

  if ($done) {
    echo "Tabulka vytvoøena.";
  }
  
?>
