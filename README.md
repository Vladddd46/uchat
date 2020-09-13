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
  <li><b>libmx</b> - helpful general functions.</li>
  <li><b>utils</b> - helpful specific functions.</li>
  <li><b>GTK3</b> - for grafical user interface.<b>(!must be preinstalled in your system.<a href="https://www.gtk.org/docs/installations/linux">installation link</a>)</b></li>
  <li><b>sqlite3</b> - database communication.<b>(!must be preinstalled in your system.<a href="https://www.tutorialspoint.com/sqlite/sqlite_installation.htm">installation link</a>)</b></li>
 </ul>

<h2>Compilation</h2>
<ul>
  <li>Just write <b>`make`</b> in root directory.</li>
  <li>After successful compilation <b>./client/uchat</b> and <b>./server/uchat_server</b> files will appear.</li>
  </ul>
  
<h2>Quickstart</h2>
<ul>
  <li>First of all you need to start server: <b>cd server; ./uchat_server port_number(<i>ps. I use port 1500</i>)</b></li>
  <li>After server starts, you are able to run client. Go to <b>./client</b> and write <b>./uchat 0.0.0.0 1500</b></li>
  <li>Bingo</li>
</ul>

![ezgif com-video-to-gif (1)](https://user-images.githubusercontent.com/11888485/93016578-ff153400-f5ca-11ea-8356-11088ec85754.gif)



