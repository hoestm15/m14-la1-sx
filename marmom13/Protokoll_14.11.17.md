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
## Übungen in Atmel Studio  
### Erstes Beispiel  

```c
int main (void)  
{  
   volatile unsigned char x;  
   x = 12;  
   return x;  
} 
```







