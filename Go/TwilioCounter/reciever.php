<?php
        header('content-type: text/xml');
        echo"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        $name = $_POST['Body'];
        $html = file_get_contents('http://0.0.0.0:9999/?sms='.$name);
?>
<Response>
        <Sms>Thanks for voting for <? echo $name ?>!</Sms>
</Response>
