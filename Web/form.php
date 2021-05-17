<!DOCTYPE HTML>
<html>
  <head>
    <meta http-equiv="content-type" content="text/html; charset=utf-8">
    <title>Jo - Prestizni Skola</title>
  </head>
  
  <body>
    <form method="post">
      <input type="text" name="jmeno" placeholder="Jmeno pokemona">
      <input type="number" name="level" placeholder="Level pokemona" min=1>
      <input type="date" name="vznik" placeholder="Vznik pokemona">
      
      <input type="submit" name="sub" value="Odeslat">
    </form>
    
    <?php
      include_once("spojeni.php");
    
      if ($_POST) {
        $jmeno = $_POST['jmeno'];
        $level = $_POST['level'];
        $vznik = $_POST['vznik'];
        
        $done = mysqli_query($spojeni, "INSERT INTO pok VALUES(NULL,'$jmeno','$level','$vznik')");
        
        if ($done) {
          echo "Vlozeno.";
        }
      }
    
    ?>

  </body>
</html>
