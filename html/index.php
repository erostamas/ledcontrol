<html>
<body>

<?php
function send_command()
{
    $sock = stream_socket_client('unix:///ledcontrol_files/ledcontrol_socket_file', $errno, $errstr);
    if (!$sock) {
        echo "$errstr ($errno)<br />\n";
    } else {
        fwrite($sock, $_POST["command"]);

        fclose($sock);
        echo "last command: ".$_POST["command"];
    }
}
send_command();
?>

<form action="index.php" method="post">
Command: <input type="text" name="command"><br>
<input type="submit"><br>
</form>

RED:     <span id="red"></span><br>
GREEN:   <span id="green"></span><br>
BLUE:    <span id="blue"></span><br>

<script>

function refresh() {
var xhttp = new XMLHttpRequest();
xhttp.open("GET", "data.xml", true);
xhttp.responseType = 'document';
xhttp.overrideMimeType('text/xml');

xhttp.onload = function () {
    if (xhttp.readyState == xhttp.DONE && xhttp.status == 200) {
        xmlDoc = xhttp.responseXML;
        var red = xmlDoc.getElementsByTagName("red")[0].childNodes[0].nodeValue;
        var green = xmlDoc.getElementsByTagName("green")[0].childNodes[0].nodeValue;
        var blue = xmlDoc.getElementsByTagName("blue")[0].childNodes[0].nodeValue;
        
        document.getElementById("red").innerHTML = red;
        document.getElementById("green").innerHTML = green;
        document.getElementById("blue").innerHTML = blue;
        document.body.style.backgroundColor = 'rgb(' + red + ',' + green + ',' + blue + ')';
    }
}
xhttp.send();

setTimeout(refresh, 1000);
}

refresh();
</script>

</body>
</html>
