# 3.Einheit: 24.10.2017

Gegenstand: LA1  
Name: Gert Enzi  
KN: 5  
Klasse: 4AHME  
Gruppe: 1  

# Fortsetzung Atmel-Studio  
## Wiederholung der letzten Einheit  
Siehe: [2.Einheit](https://github.com/HTLMechatronics/m14-la1-sx/edit/enzgem13/enzgem13/2_Einheit.md)  
  
## Erstellen eines neuen Programmes mit Atmel Studio  

Zuerst wird ein C-Programm erstellt und im Debug-Modus ausgeführt.  
Das Programm lautet wie folgt:  
```c
int main(void)
{
  volatile unsigned char a;
  a=10;
  return a;
}
```  
Nun mithilfe von *Debug -> Windows -> Disassembly* die Liste von ausgeführten Assembler-Befehle aufrufen.  
Das Schlüsselwort **volatile** bestimmt, ob eine Optimierung des Befehls ausgeführt werden soll. Mit dem voraus gesetzten **volatile** ist es uns möglich die genauen Assemblerbefehle zu sehen, die z.B.: während des Anlegens einer Variable verwendet werden.  
Der Start des Programmes läuft auf gleiche Weise wie in der 2.Einheit bereits beschrieben ab. Jedoch wird diesmal im Register *R24* die Konstante ```0x0a -> 10``` abgelegt und darauf wird die Variable in *R24* abgelegt. Die Konstante in *R24* wird am Stack abgelegt und am Ende wieder freigegeben (**POP**).  
  
## Addition  
Wiederum ein Programm erstellen:  
```c
int main(void)
{
  volatile unsigned char a = 10;
  volatile unsigned char b = 8;
  return a + b;
}
```  
Was bei diesem Programm heraussticht ist, dass zunächst mit dem Befehl **RCALL** 2 Bytes auf dem Stack für die beiden Variablen reserviert werden. Das Anlegen der Variablen funktioniert nach dem gleichen Prinzip wie bereits oben beschrieben. Das Addieren an sich ist ebenso recht einfach gelöst, da der Prozessor eigene Befehle für eine Addition (auch für z.B. Multiplikation) hat. In diesem Fall ist es der Befehl **ADD**. Der Wert wird ins vorgegebene Register (in unserem Fall ist es R18) gespeichert.  
  
## Zusammenfassung  
Man sieht anhand der Assembler Befehle, die notwendig sind, um einen C-Befehl auszuführen, dass oftmals großer Aufwand für den Prozessor dahinter steckt, allerdings gibt es ebenso Fälle, in denen der Prozessor einen eigenen Befehl für eine bestimmte Aufgabe hat (Addition, Multiplikation). Für Aufgaben wie eine Division beispielsweise, sind viel mehr einzelne Befehle notwendig, was sich wiederum auf die Schnelligkeit der Abarbeitung des Programmes auswirkt. 
