# Protokoll - 06.02.2018
Name: Michael Mörth  
Klasse: 4AHME  
Gruppe: 2  

Anwesend: Nebel Florian, Mandl Gerhard, Michael Mörth, Moritz Martinak, Mario Nabernik, Muri Lorenz, Platzer Andreas, Marcel Köhler    
Abwesend: -

## Wiederholung vom Compiliervorgang
### Compilevorgang
Zu Beginn der Stunde begannen wir damit, noch einmal den "Compilevorgang" zu besprechen.  
**Die Tabelle zeigt den Übersetzungsvorgang eines C-Programmes für den Atmega328p**

Vorhaben | Befehl zum umwandeln | Beschreibung
--------------- | --------- | ---------
`main.c`zu `main.o` | avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c | `-mmcu` gibt an um welches System es sich handelt .`-c` sorgt dafür das nur kompiliert wird (der Linker wird nicht gestartet). `-DF_CPU=16000000L` gibt die Taktfrequenz an.
`main.o`zu `main.elf`| avr-gcc -o main.elf main.o | `-o` sorgt dafür das nur gelinkt wird. `main.elf` ist die Zieldatei und `main.o` die Quelldatei
`main.elf` zu `main.hex` | avr-objcopy -O ihex main.elf main.hex | `ihex` gibt an, dass die Datein im [Intel-Hex](https://de.wikipedia.org/wiki/Intel_HEX) Format gespeichert wird. `main.elf` ist die Quelldatei und `main.hex` die Zieldatei

#### Informationen zum Compiliervorgang
Im ersten Schritt wird die Datei `main.c` zur Objektdatei `main.o` übersetzt. In diesem Vorgang werden vom *Preprozessor* alle Header-Dateien eingebunden. Beim *Compilen* wird der Quelltext dann in [Assemblerbefehle](https://de.wikipedia.org/wiki/Assembler_(Informatik)) übersetzt. Beim *Assemblieren* wird der Assemblerquelltext dann in binäre Maschinenbefehle übersetzt.

Im zweiten Schritt wird die Objektdatei `main.o` zur ausführbaren (*executable*) Datei `main.elf` übersetzt. Dieser Vorgang wird *Linken* genannt. Hier werden alle tatsächlichen Adressen eingetragen, wodurch das Programm ausgeführt werden kann.

Der dritte Schritt wird nur benötigt, wenn das System die `main.elf` nicht ausführen kann. Die Datei `main.elf` wird zur Hex-Datei `main.hex` übersetzt. Dieser Vorgang wird *Konvertieren* genannt.

## Makefiles
Normalerweise werden C-Files in IDEs (Integrated Development Enviroment) wie zum Beispiel Netbeans & Codeblocks programmiert. BeiÜbersetzungsvorgang wird dann auf das Übersetzungstool *make* zurückgegriffen.

### make
> make (englisch für machen, erstellen) ist ein *Build-Management-Tool*, das Kommandos in Abhängigkeit von Bedingungen ausführt. Es wird hauptsächlich bei der Softwareentwicklung als Programmierwerkzeug eingesetzt.
> Genutzt wird es beispielsweise, um in Projekten, die aus vielen verschiedenen Dateien mit Quellcode bestehen, **automatisiert alle Arbeitsschritte** (Übersetzung, Linken, Dateien kopieren etc.) **zu steuern**, bis hin zum fertigen, ausführbaren Programm. make ist jedoch so flexibel ausgelegt, dass es auch beliebige andere Aufgaben steuern kann, bei denen die zeitliche Abhängigkeit von Dateien eine Rolle spielt.
> Das Hilfsprogramm make ist Teil des POSIX-Standards, dessen gegenwärtige Bezeichnung **IEEE Std 1003.1, 2008 Edition** lautet (äquivalent dazu Single UNIX Specification V3, SUSv3).
 
*Quelle: [Wikipedia](https://de.wikipedia.org/wiki/Make)*

**Zusammenfassung:**
Zusammengefasst kann man sagen, dass Makefiles eine Liste von Terminal-Commands zurÜbersetzung von Programmensind. Diese Terminal-Commands werden nur ausgeführt, wenn bestimmte Bedingungen erfüllt sind. Die Befehle werden anschließend automatisiert abgearbeitet. Makefiles sind auf allen Unix-basierenden Betriebssystem lauffähig.

### Aufbau von Makefiles
```
Ziel 1: Voraussetzung 1, ... , Voraussetzung n  
[Tab] Kommando 1  
[Tab] ...  
[Tab] Kommando n  

Ziel 2: Voraussetzung 1, ... , Voraussetzung n  
[Tab] Kommando 1  
[Tab] ...  
[Tab] Kommando n  
```

### Aufruf von `make` im Terminal
Um Makefiles aufzurufen muss man einfach das Kommando `make` im Terminal eingeben. Makefiles versuchen immer so effektiv wie möglich zu arbeiten.Um dies zu erreichen vergleicht das Makefile vor dem Durchlauf die *Zeitstempel* der Dateien und entscheidet danach, ob das Kommando ausgeführt werden muss. Das Makefile wird dann die Ziele abhängig von den Voraussetzungen abgearbeitet.

#### Zeitstempel in Makefiles
Die Verwendung der Zeitstempel kann durch folgendes Beispiel beschrieben werden. Möchte man zum Beispiel aus einer `main.c` eine `main.o` erzeugen, werden dann alle Kommandos des Ziels `main.o` ausgeführt. Wird das Makefile dann wieder aufgerufen und die Datei `main.o` hat einen neueren Zeitstempel als die Datei `main.c`, wird die Datei `main.o` nicht neu erstellt.

## Aufgabe 1
Unsere erste Aufgabe war es mit Hilfe eines Makefiles ein C-Programm aus dem FIVU-Unterrichts übersetzen. Das Programm soll danach auf unserem Atmega328p lauffähig sein.

### Quelltext des C-Programmes
```c
#include <avr/io.h>
#include <util/delay.h>

int main()
{
        DDRB = (1<<PB5);
        while(1)
        {
                PORTB=(1<<PB5);
                _delay_ms(500);
                PORTB = 0;
                _delay_ms(500);
        }
        return 0;
}
```
### Quelltext Makefile
```
main.hex: main.elf
        avr-objcopy -O ihex main.elf main.hex

main.elf: main.o
        avr-gcc -o main.elf main.o

main.o: main.c
        avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c

clean:
        -rm main.o
        -rm main.elf
        -rm main.hex
```
#### Details zum Makefile

Befehl | Beschreibung
------ | ------------
`main.o: main.c` | Die Datei `main.c` wird übersetzt. In der Datei `main.o` stehen dann die Maschinenbefehle.
`main.elf: main.o` | Die Datei mit `main.o` wird gelinkt. Es werden alle Adressen vergeben.
`main.hex: main.elf` | Die Datei mit `main.elf` wird zur Hex-Datei `main.hex` umcodiert.
`clean:`| Es werden alle angegeben Dateien aus dem Verzeichnis gelöscht.

> Wenn eine angegeben Datei im Verzeichnis nicht vorhanden ist liefert das Kommando `rm` einen Rückgabewert != 0 (Fehler aufgetreten). Für das Makefile bedeutet das, dass die Abarbeitung des Makefiles abgebrochen wird. Das `-` vor dem Kommando `rm` wird benötigt, um einen Abbruch des Programmes zu verhindern. 

#### Aufrufmöglickeiten

Befehl | Beschreibung
------ | ------------
`make` | Führt die Kommandos des ersten Ziels des Makefiles durch.
`make clean` | Führt die Kommandos des Ziels `clean` aus. Es werden alle angegebenen Dateien aus dem Verzeichnis gelöscht.
`make main.o` | Übersetzt die Datei `main.c` in den Maschinencode.
`make main.elf` | Trägt die Adressen im Maschinencode ein. Die Datei ist ausführbar.
`make main.hex` | Die Datei `main.elf` wird in eine Hex-Datei umcodiert.
