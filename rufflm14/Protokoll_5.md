# **5. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 16.03.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: keiner

## **Beschreibung der Aufgabenstellung**

Es soll eine Temperaturmessung über den am SURE-Board integrierten Temperatursensor erfolgen. Die Messdaten sollen am PC über ein **JAVA-Programm** ausgegeben werden. Dafür steht bereits eine vorgefertigte GUI (JAVASwing) zur Verfügung. Auch für den µC ist das Programm bereits vorgegeben.  müssen über ein Bussystem ausgetauscht.

## **Realisierung**

Die grundsätzliche Struktur sieht folgendermaßen aus:

![Grundstruktur als SVG](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/BildGrundstruktur.svg)

Der  **Temperaturensor LM75** gibt die Messdaten an das Rechenzentrum des Mikrocontrollers über I²C weiter. Während der LM75 hier als _unintelligenter_ Sensor agiert, kann das **SURE-Board** als Ganzes durchaus als _intelligenter_ Sensor bezeichnet werden. Der Mikorcontroller gibt die Messdaten über UART weiter. Die Verbindung zwischen dem SURE-Board und dem PC (MiniUSB/USB) ist in diesem Fall ein **Feldbus**.

[Weitere Informationen zum LM75](http://www.franksteinberg.de/lm75.htm)

### UART

Der UART ist eine einfache **serielle Schnittstelle**, die in Bezug auf Datenübertragungsrate, Anzahl der Stop-Bits und Even Parity/Uneven Parity konfiguriert werden kann. UART steht für **U**niversial **A**synchronous **R**eceiver **T**ransmitter. 

[Weitere Informationen zum UART](https://www.mikrocontroller.net/articles/AVR-Tutorial:_UART)

### JAVA Swing 

Die grafische Benutzeroberfläche (**GUI**) wurde mittels JAVA Swing programmiert. JAVA Swing ist unter Java die standardmäßige Lösung für GUIs. Die Einarbeitungszeit hält sich in Grenzen und im Normalfall reicht die zu Verfügung stehenden  Controls zur Darstellung aus. JAVA Swing ist seit 1998 Bestandteil der JAVARuntime und weit verbreitet. Als designierter Nachfolger kam 2014 JavaFX heraus, der Lücken im Bereich Medien und Animation schließen sollte. JavaFX wurde bisher aber nicht so stark angenommen wie erhofft.

[Weitere Informationen zu JAVA Swing](https://de.wikipedia.org/wiki/JavaFX)
[Weitere Informationen zu JAVA FX](https://de.wikipedia.org/wiki/Swing_(Java))

### Feldbus




