<h1>Uchat</h1>
<p><b>Desktop application for online messaging</b><p>

<h2>Project structure</h2>
<ul>
  <li><b>./libs</b> - folder, which contains external libraries.</li>
  <li><b>./client</b> - folder with client side of application</li>
  <li><b>./server</b> - folder with server side of application</li>
 </ul>

<h2>External libraries</h2>
<ul>
  <li><b>CJSON</b> - json parser library.</li>
  <li><b>crypt</b> - library with cryptography.</li>
  <li><b>libmx</b> - helpful general functions</li>
  <li><b>utils</b> - helpful specific functions</li>
 </ul>



Application for messaging. Repository contains server and client side.
--** Server **--
Server handles incomming connections by multiplexing sockets. select() system call is used for this purpose.

--** Client **--
GTK+3 for GUI
sqlite3
cJSON


