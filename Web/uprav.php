<!DOCTYPE HTML>
<html>
  <head>
    <meta http-equiv="content-type" content="text/html; charset=utf-8">
    <title>Jo - Prestizni Skola</title>
  </head>
  
  <body>
    <?php
      include_once("spojeni.php");
    
      if ($_POST) {
        $jmeno = $_POST['jmeno'];
        $level = $_POST['level'];
        $vznik = $_POST['vznik'];
        
        $done = mysqli_query($spojeni, "UPDATE pok SET jmeno = '$jmeno', level = '$level', vznik = '$vznik' WHERE id = ". $_GET['id']);
      
        if ($done) {
          header("location:vypis.php");
        }
      }
    
      $data = mysqli_query($spojeni, "SELECT * FROM pok WHERE id = ". $_GET['id']);
    
      if ($data && $row = mysqli_fetch_assoc($data)) {
        echo '
          <form method="post">
            <input type="disabled" value="'. $row['id'] .'">
            <input type="text" name="jmeno" placeholder="Jmeno pokemona" value="'. $row['jmeno'] .'">
            <input type="number" name="level" placeholder="Level pokemona" min=1 value="'. $row['level'] .'">
            <input type="date" name="vznik" placeholder="Vznik pokemona"  value="'. $row['vznik'] .'">
            
            <input type="submit" name="sub" value="Upravit">
          </form>';
      } else {
         echo 'Zaznam neexistuje.';
      }
    
    ?>

  </body>
</html>
