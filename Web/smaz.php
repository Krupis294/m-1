<?php
  include_once("spojeni.php");
  
  $done = mysqli_query($spojeni, "DELETE FROM pok WHERE id = ". $_GET['id']);
  
  if ($done) {
    header("location:vypis.php");
  }
?>
