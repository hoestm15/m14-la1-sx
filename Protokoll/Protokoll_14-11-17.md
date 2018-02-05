# Protokoll der 3. Einheit

## 3. Einheit

* Name: Mario Nabernik  
* Klasse: 4AHME  
* Datum 14.11.2017  
* Gruppe: 2  
* Anwesend: Marcel Köhler, Michael Mörth, Florian Nebel, Lorenz Muri, Moritz Martinak, Andreas Platzer, Mario Nabernik, Gerhard Mandl  
* Abwesend: -  
* Thema: Atmel Studio

## Zu Beginn der Einheit  
Zu Beginn der Einheit besprachen wir nochmal all das, dass wir in der vorigen Einheit durchgemacht haben. Darunter waren alle durchbesprochenen 
Befehle und theoretisches wie zum Beispiel die Funktion des Stackspeichers oder der Aufbau eines Mikrocontrollers
(siehe auch [2. Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/nabmam14/Protokoll/Protokoll_07-11-17.md)). 

## Heartbleed Bug  
### Was ist das?
Hier handelt es sich um einen schweren Programmfehler, durch den über verschlüsselte
TLS-Verbindungen private Daten von Clients und Servern ausgelesen werden können.
Der Fehler befindet sich in der OpenSSL-Implementierung der Heartbeat-Erweiterung für die Verschlüsselungsprotokolle TLS und DTLS.  
  
### Funktion
Hier geht es um den lesenden Zugriff über die Grenzen eines Datenpuffers (buffer over-read). Im Gegensatz zum Pufferüberlauf werden hier keine Daten
außerhalb der Puffergrenze geschrieben. Der Programmierer erklärte, er habe
einen unabsichtlichen Programmierfehler
begangen und die Prüfung einer Eingabevariable versäumt,in der die Länge des zurückzuliefernden Puffers mitgeteilt wird.

## Beispiele in Atmel Studio  
### Beispiel 1 
```c
int main (void)  
{  
   volatile unsigned char x;  
   x = 12;  
   return x;  
} 
```
  
__unsigned char__: Dieser Datentyp kann im Gegensatz zu `char` oder `signed char` vorzeichenlose Zahlen von 0 bis 255 on einem Byte speichern.  
  
__volatile__: Dieses Schlüsselwort bietet uns die Einsicht in die Erstellung einer Variable. Ohne ihm wäre das nur bedingt möglich.  
  
Nach dem dissemblieren im Debugging Modus des obigen Beispiels hatten wir Einsicht über die einzelnen Befehle:  
  
Maschinenbefehl | Geschrieben | Funktion  
--------------- | --------- | ---------  
`cf.93` | __PUSH__ R28 | Register R28 wird auf den Stack gelegt.  
`df.93` | __PUSH__ R29 | Register R29 wird auf den Stack gelegt.  
`1f.92` | __PUSH__ R1 | Register R1 wird auf den Stack gelegt.  
`cd.b7` | __IN__ R28,0x3D | 0x3D wird aus dem I/O-Register in R28 geladen.  
`de.b7` | __IN__ R29,0x3E | 0x3E wird aus dem I/O-Register in R29 geladen.  
`8c.e0` | __LDI__ R24,0x0C | Die Konstante 0C wird im Register R24 abgelegt.  
`89.83` | __STD__ Y+1,R24 | Konstante aus R24 wird am Speicherplatz des Stacks der lokalen Variable abgelegt.  
`89.81` | __LDD__ R24,Y+1 | Die Variable wird in Register R24 geladen.  
`90.e0` | __LDI__ R25,0x00 | Rückgabewert  
`0f.90` | __POP__ R0 | Variable wird freigegeben.  
`df.91` | __POP__ R29 | Register R29 wird vom Stack entfernt.  
`cf.91` | __POP__ R28 | Register R28 wird vom Stack entfernt. -> (R29 muss zuerst enfernt werden LIFO (_Last in First out_ - Prinzip)   
  
### Beispiel 2  
```c
int main (void)  
{  
   volatile unsigned char a = 12;  
   volatile unsigned char b = 8;  
   return a+b;  
} 
```
  
Nach dem dissemblieren im Debugging Modus des obigen Beispiels hatten wir Einsicht über die einzelnen Befehle (folgende Befehle sind nur jene, welche im vorigen Beispiel nicht benötigt wurden, bei der Addition hingegen schon):
  
Maschinenbefehl | Geschrieben | Funktion  
--------------- | --------- | ---------  
`00.d0` | __RCALL__ PC+0x0001 | Springt zum nächsten Befehl.  
`88.e0` | __LDI__ R24,0x08 | Die Konstante 08 wird im Register R24 abgelegt.  
`2a.81` | __LDD__ R18,Y+2 | Variable b wird in Register R18 geladen.  
`30.e0` | __LDI__ R19, 0x00 | Konstante 0x00 wird am Register R19 abgelegt.  
`28.0f` | __ADD__ R18,R24 | Die beiden Register werden addiert, ohne Berücksichtigung des Carry-Flags. Das Endergebnis wird in R18 gespeichert.  
`31.1d` | __ADC__ R19,R1 | Addition mit Berücksichtigung des Carry-Flags.  
  
### Beispiel 3  
```c
int main (void)  
{  
   volatile a = 10;  
   uint8_t b;  

   for (b=0; b<10; b++)  
   {  
   }  
   return 0;  
} 
```
  
### Beispiel 4  
```c
int main (void) <br>
{  
   volatile unsigned char a = 12;  
   volatile unsigned char b = 8;  
	  
   return a*b;  
} 
```
  
### Beispiel 5  
```c
int main (void)  
{  
   volatile unsigned char a = 12;  
   volatile unsigned char b = 8;  
	
   return a/b;  
} 
```
  
Das Besondere an einer Division ist, dass dem __AT328P__ keine Befehle oder Tabellen zur Verfpgung stehen. Bei einer 
Addition/Subtraktion/Multiplikation hingegen schon. Das ist der Grund, weshalb er beim dividieren deutlich länger braucht.  
