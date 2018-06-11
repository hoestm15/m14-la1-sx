# Protokoll 24.04.2018  

## 7. Einheit  

## Thema: Schnittstellenprogrammierung

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 24.04.2018  
Abwesend: -  

## Wiederholung  

### Besprechung des Programs  
Zu beginn der Stunde besprachen wir das Programm welches wir in der letzen Einheit zu programmieren begonnen hatten. Diese findet man im [letzen Protokoll](https://github.com/HTLMechatronics/m14-la1-sx/blob/marmom13/marmom13/Protokoll_27.02.18.md).  Ausserdem haben wir noch über das Java Native Interface (JNI) gesprochen.  

### Java Native Interface (JNI)  
>Java kann nicht wirklich eine plattformunabhängige Programmiersprache sein – spätestens, wenn es an die tatsächlichen Ressourcen eines Rechners geht, müssen diese in Java eingebunden werden. Ein Sortierverfahren oder eine Datenstruktur ist wirklich plattformneutral, für das Bearbeiten von Dateien oder das Setzen von Punkten auf dem Bildschirm ist jedoch die jeweilige Architektur zuständig. Dazu ruft Java die nativen Methoden auf, die nicht in Java implementiert sind. Native Methoden sind in der>API-Dokumentation nicht immer zu erkennen, aber ein Blick in den Quellcode verrät sie schnell.  

>Um diese Schnittstelle zwischen Java und konkreter Plattform kümmert sich das Java Native Interface (JNI). Mithilfe von JNI können aus der JVM heraus plattformspezifische Funktionen verwendet werden. Die native Funktion – wir gehen im Folgenden von einer Funktion in C aus – kann aber auch wieder die JVM steuern und Objekte erfragen, Ausnahmen auslösen, neue Klassen laden usw. 

*Quelle: [Java 7: Mehr als eine Insel](http://openbook.rheinwerk-verlag.de/java7/1507_21_001.html)
