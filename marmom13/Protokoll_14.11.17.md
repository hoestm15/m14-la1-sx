# Protokoll 14.11.2017  

## 3. Einheit  

## Thema: Atmel Studio

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 14.11.2017  
Abwesend: -  

## Heartbleed Bug  
### Definition  
"Der Heartbleed-Bug ist ein schwerwiegender Programmfehler in älteren Versionen der Open-Source-Bibliothek OpenSSL, durch den über verschlüsselte TLS-Verbindungen private Daten von Clients und Servern ausgelesen werden können. Der Fehler betrifft die OpenSSL-Versionen 1.0.1 bis 1.0.1f und wurde mit Version 1.0.1g am 7. April 2014 behoben. Ein großer Teil der Online-Dienste, darunter auch namhafte Websites wie auch VoIP-Telefone, Router und Netzwerkdrucker waren dadurch für Angriffe anfällig."  
(Quelle: [https://de.wikipedia.org/wiki/Heartbleed](https://de.wikipedia.org/wiki/Heartbleed))    
### Entstehung  
"Bei der Sicherheitslücke handelt es sich um einen lesenden Zugriff über die Grenzen eines Datenpuffers (buffer over-read). Anders als bei einem Pufferüberlauf werden keine Daten außerhalb von Puffergrenzen geschrieben. Der Programmierer erklärte, er habe einen unabsichtlichen Programmierfehler begangen und die Prüfung einer Eingabevariable versäumt,[8][9] in der die Länge des zurückzuliefernden Puffers mitgeteilt wird. Sein Fehler sei zwar trivial, aber folgenreich gewesen. Ferner stellte er fest, dass sein Fehler offensichtlich deshalb nicht bemerkt worden sei, weil zu wenige Menschen den Code von OpenSSL tatsächlich überprüfen."  
(Quelle: [https://de.wikipedia.org/wiki/Heartbleed](https://de.wikipedia.org/wiki/Heartbleed))    
## Übungen in Atmel Studio  ![Bild]( m14-la1-sx/marmom13/Atmel studio.jpg )
### Erstes Beispiel  

```c
int main (void)  
{  
   volatile unsigned char x;  
   x = 12;  
   return x;  
} 
```  
__Datentyp Character (char):__ "Ein Character repräsentiert die kleinste adressierbare Einheit in C, in der Regel acht Bit. Deshalb wird die Größe von Objekten und Typen oft als ganzzahliges Vielfaches eines Characters angegeben. Je nach Compiler kann char entweder gleichbedeutend sein mit signed char (-128 bis 127, fast immer der Fall) oder mit unsigned char (0 bis 255). Um auch Zeichen aus Zeichensätzen aufnehmen zu können, die mehr Zeichen umfassen als der relativ kleine ASCII-Zeichensatz, wurde mit wchar_t bald ein zweiter für Zeichen konzipierter Datentyp eingeführt. Er umfasst in fast allen Implementierungen mehr als acht Bit."  
(Quelle: [https://de.wikipedia.org/wiki/Datentypen_in_C](https://de.wikipedia.org/wiki/Datentypen_in_C))    

__Schlüsselwort volatile:__ "Volatile ist ein Zusatz bei der Deklaration von Variablen in Programmiersprachen wie C, C++, Java oder C#.
In C und C++ wird durch diesen Typqualifikator spezifiziert, dass sich der Wert der Variable jederzeit ändern kann, beispielsweise durch andere Prozesse, Threads oder sogar externe Hardware.[1] Bei der Generierung des Maschinen-Codes aus einem in C oder C++ geschriebenen Programm verhindert die Kennzeichnung einer Variablen als volatile eine in diesem Fall die Funktionalität beeinträchtigende Optimierung, so dass das Programm immer auf den tatsächlich in der Hardware vorhandenen Wert zugreift." (Quelle: [https://de.wikipedia.org/wiki/Volatile_(Informatik)](https://de.wikipedia.org/wiki/Volatile_(Informatik))  

Wir dissemblierten das Programm im Debugging Modus und schauten uns die einzelnen Maschienenbefehle genau an.    

### Zweites Beispiel  

```c
int main (void)  
{  
   volatile unsigned char a = 12;  
   volatile unsigned char b = 8;  
   return a+b;  
} 
```
Ähnlich wie auch bei dem ersten Beispiel dissembliereten wir das Programm im Debugging Modus. Die Maschienenbefehle überschnitten sich zum größten Teil mit der ersten Übung, nur die Befehle die für die Addition benötigt wurden änderten sich. (Das gleiche Trifft auch auf alle anderen folgende Beispiele zu).   

### Drittes Beispiel  

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

### Viertes Beispiel  

```c
int main (void) <br>
{  
   volatile unsigned char a = 12;  
   volatile unsigned char b = 8;  
	  
   return a*b;  
} 
```    

### Fünftes Beispiel  

```c
int main (void)  
{  
   volatile unsigned char a = 12;  
   volatile unsigned char b = 8;  
	
   return a/b;  
} 
```
