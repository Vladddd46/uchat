<h1>Uchat</h1>
<p><b>Desktop application for online messaging</b><p>

<h2>Project structure</h2>
<ul>
  <li>./libs - folder, which contains external libraries.</li>
  <li>./client - folder with client side of application</li>
  <li>./server - folder with server side of application</li>
 </ul>




Application for messaging. Repository contains server and client side.
--** Server **--
Server handles incomming connections by multiplexing sockets. select() system call is used for this purpose.

--** Client **--
GTK+3 for GUI
sqlite3
cJSON


