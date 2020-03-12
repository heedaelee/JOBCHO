<h1 align = "center">JOBCHO</h1>
<p align="center">
<img src="image/jobcho_logo.png" width="10%" height="10%"></br>
</p>

<h2 align="center">Overview</h2>
<p align="center">
This repository has source of project, "JOBCHO".<br>
"JOBCHO" project is controlling bundle of pressure sensor, made of velostat.
</p>


<h2 align="center">Prerequistory</h2>
<p align="center">
  velostat mat x 1</br>
  main board x 1</br>
  demux module x 2</br>
  mux module x 1</br>
  7x2 IDC connector x 3</br>
  8x2 IDC connector x 6</br>
</p>

<h2 align="center">Quick start</h2>
<p align="center">

</p>

<p align="center">
1. First, you have to connect flat wire to sensor mat.</br>
  <img src="image/quick_start_1.PNG" width="50%" height="50%"></br>
<p align="center">
2. Next, connect USB cable to your computer.</br>
3. execute ./python files/main.py or execute main.exe file.</br>
<img src="image/quick_start_2.PNG" width="50%" height="50%"></br>
<p align="center">
4. select your arduino port and press 'connect' button. </br>
<img src="image/quick_start_3.PNG" width="50%" height="50%"></br>
<p align="center">
5. Now, you can see visualized sensor data.</br>
  <img src="image/quick_start_4.PNG" width="50%" height="50%"></br>
<p align="center">
  <img src="image/quick_start_5.PNG" width="50%" height="50%"></br>
<p align="center">
6. adjust two parameter(sensitivity, threshold) to remove noise, and amplify signal.</br>
Our team found some optimized value for two value.</br>

<div align = "center">
  
  <table>
      <thead>
          <tr>
              <th align="center">motion</th>
              <th align="center">sensitivity</th>
              <th align="center">threshold</th>
          </tr>
      </thead>
      <tbody>
          <tr>
              <td align="center">walking</td>
              <td align="center">30</td>
              <td align="center">200</td>
         </tr>
          <tr>
              <td align="center">lying</td>
              <td align="center">40</td>
              <td align="center">200</td>
          </tr>
      </tbody>
  </table>
  
</div>
