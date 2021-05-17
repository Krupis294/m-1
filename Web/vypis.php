<?php
  include_once("spojeni.php");
  
  $data = mysqli_query($spojeni, "SELECT * FROM pok");
  
  echo '<table>   
          <tr>
            <th>ID</th>
            <th>Jmeno</th>
            <th>Level</th>
            <th>Vznik</th>
          </tr>
  ';
  
  while($row = mysqli_fetch_assoc($data)) {
    echo '
      <tr>
        <td>'. $row['id'] .'</td>
        <td>'. $row['jmeno'] .'</td>
        <td>'. $row['level'] .'</td> 
        <td>'. $row['vznik'] .'</td>
        <td><a href="uprav.php?id='. $row['id'] .'">Upravit</a></td>
        <td><a href="smaz.php?id='. $row['id'] .'">Smazat</a></td>
      </tr>';  
  }
  
  echo '</table>';

?>
