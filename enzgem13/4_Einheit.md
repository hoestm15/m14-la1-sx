# 4.Einheit: 16.01.2018

Gegenstand: LA1  
Name: Gert Enzi  
KN: 5  
Klasse: 4AHME  
Gruppe: 1  

# Makefiles  
## Was sind Makefiles?  
Makefiles sind Textdateien, die dazu verwendet werden können einen Übersetzungsvorgang zu steuern. Man kann sie aber auch zu anderen
Zwecken nutzen. Kurz gesagt sind es Dateien, die das Arbeiten mit Befehlen oder Programmen einfacher und übersichtlicher gestalten können.  
  
## Verwendung von Makefiles  
Um den für Makefiles reservierten Befehl **make** nutzen zu können, benötigt man eine Steuerdatei. Diese hat in den meisten Fällen den
dafür vorgesehenen Namen *Makefile*, kann aber auch andere Namen haben (muss man jedoch als Information hinzufügen).  

### Aufbau eines Makefiles  
**Makefile**
```
Ziel1: Abhängigkeiten 
  ->  Kommando 1
  ->  Kommando 2
  ->  ..........

Ziel2: Abhängigkeiten
  ->  Kommando 1
  ->  Kommando 2
  ->  ..........
```
Die Ziele (Targets) und Abhängigkeiten (Dependencies) können Dateien sein (in unserem Fall z.B.: main.c, main.o ...), müssen es aber nicht
sein. Man kann ebenso Symbole dafür verwenden.  
Beispiel:
```
clean:            - ist nun ein Symbol ohne Abhängigkeiten
  ->  rm main.o   - in diesem Fall wird die Datei main.o "removed" also entfernt
```
Für die Kommandos (Commands) ist es wichtig, dass man davor wie oben gezeigt einen Tabulator verwendet, sonst kommt es zu einer 
Fehlermeldung und die Befehle können nicht weiter ausgeführt werden.  

### Wie arbeitet ein Makefile?
Beim Aufruf des Befehls **make** wird das komplette Makefile einmal durchlaufen. Dabei zu beachten ist, dass ab einem Fehler der Abbruch
des Vorgangs stattfindet. Darum ist es wichtig bei Befehlen oder Aufgaben, die unbedingt erfüllt werden müssen, entsprechende Zeichen vor das Kommando gesetzt werden (genauere Beschreibung später). Ein Makefile hat das Ziel, so effizient und schnell wie möglich zu arbeiten, darum vergleicht es vor jedem Durchlauf den *Zeitstempel* von allen Dateien. Somit weiß es, welche Aufgabe erneut durchgeführt werden muss.  

z.B.: Ich will *main.o*->Ziel mithilfe von *main.c*->Abhängigkeit erstellen. Ist nun eine *main.o* beriets vorhanden und die *main.c* hätte sich geändert, würde der das Kommando erneut durchlaufen werden. Hat sich aber in *main.c* nichts geändert, sprich ist der Zeitstempel von *main.c* älter als der von *main.o* würde man als Rückmeldung: *make: "main.o" ist bereits aktuell.* erhalten.  
  
## Übersetzung eines C-Programmes mit hilfe von Makefiles  
Um ein Programm überhaupt übersetzten zu können, braucht man einen Quelltext. Diesen benennen wir üblicherweise *main.c*:  
```c
#define F_CPU 16000000L // Die Taktfrequenz des Atmega 328p wird angegeben

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRB = (1 << PB5);
  while (1)
  {
    PORTB ^= (1 << PB5);
    _delay_ms(500);
  }
  return 0;
}
```
  
Dieses einfache Blinklicht soll nun den Übersetzungsvorgang durchlaufen. Hierzu folgendes Makefile:  
```
all: build // -> kann man später mit make all aufrufen

build: main.hex // -> ist später durch make build aufzurufen

cleanandbuild: clean build

main.hex: main.elf
  ->  avr-objcopy -O ihex main.elf main.hex // -> Die main.elf wird in einen Hexcode umgewandelt

main.elf: main.o
  ->  avr-gcc -mmcu=atmega328p -Os -o main.elf main.o // -> Dieser Schritt wird Linker genannt - es werden die nötigen Adressen 
                                                            vergeben und die Hardware in unserem Fall der atmega328p bekanntgegeben
  
main.o: main.c
  ->  avr-gcc -mmcu=atmega328p -Os -c main.c // -> Das C-Programm wird in Assembler-Code umgewandelt
  
clean: // -> sozusagen: auf Grundzustand zurücksetzen
  ->  -rm main.o 
  ->  -rm main.elf
  ->  -rm main.hex
```
Das Zeichen "-" vor dem remove (**rm**) Befehl sorgt wie beriets oben erwähnt dafür, dass egal ob die zu löschende Datei vorhanden ist oder nicht, alle remove Kommandos durchlaufen werden.
  
Nun kann man im Terminal:  
```> make```  
aufrufen und am Bildschirm werden alle eingegebenen Befehle angezeigt und durchlaufen.  
  
Zu solch einem Vorgang gehört, wie bereits oben beschrieben, ein Aufräumbefehl (**clean**), um das Verzeichnis in dem man sich befindet 
auf seinen Grundzustand zurückzusetzen.  
Dieser wird aufgerufen mittels:  
```> make clean```    
Nun erscheinen am Bildschirm die **rm** Befehle, die im Makefile festgelegt worden sind. Kommt es nun zu einem Fehler, wenn eine Datei beispielsweise nicht mehr vorhanden ist, so erscheint eine Warnung, es werden jedoch immer noch sämtliche remove-Kommandos durchlaufen.  
Wie man sieht ist es auch möglich nur einzelne Dateien innerhalb des Makefiles zu erstellen.  
z.B.:  
```make main.o```  
Man wird feststellen dass nur die main.o erstellt wurde. Mithilfe der Abhängigkeiten ist es auch möglich, nur:  
```make main.elf```  
einzugeben, man wird feststellen dass ebenso eine *main.o* erstellt wurde, da diese Datei als Abhängigkeit für dei *main.elf* fungiert.  
