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
 
*Quelle: [Wikipedia, make](https://de.wikipedia.org/wiki/Make)*
