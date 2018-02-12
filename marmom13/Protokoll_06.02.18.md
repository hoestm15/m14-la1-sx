# Protokoll 06.02.2018  

## 4. Einheit  

## Thema: Atmel Studio

Name: Moritz Martinak  
Lehrer: sx  
Gruppe: 2  
Übungsdatum: 14.11.2017  
Abwesend: -  

# Wiederholung  

## Compilieren  

Zuerst besprachen wir den Compiliervorgang beim Compilieren einer main.c Datei für einen Atmega328p.
Dabei wird diese zuerst mit dem befehl **avr-gcc -mmcu="atmega328p" -Os -c -DF_CPU=16000000L main.c** zu einer **main.o** umgewandelt.  
Dabei gibt **-mmcu** an un welches System es sich handelt. Durch **-c** wird nur compiliert und noch nicht gelinked. **-DF_CPU=16000000L** ist die Taktfrequenz des Atmegas also 16Mhz.  

Danach wird die main.o mit dem Befehl **avr-gcc -o main.elf main.o** zu einer **main.elf** umgewandelt. main.elf ist die Zieldatei, main.o die Quelldatei. -o sorgt dafür das nur gelinkt wird.

Zu letzt wird mit **avr-objcopy -O ihex main.elf main.hex** die main.elf Datei zu einer main.hex Datei konvertiert. Das ist erforderlich um das Programm auf einem Atmega328p zu verwenden.

# Makefiles  

Für gewöhnlich programmiert man C-Programme in einer IDE, diese verwendet zum übersetzen das Tool **make**. 

## make

> make (englisch für machen, erstellen) ist ein Build-Management-Tool, das Kommandos in Abhängigkeit von Bedingungen ausführt.     Es wird hauptsächlich bei der Softwareentwicklung als Programmierwerkzeug eingesetzt.  
Genutzt wird es beispielsweise, um in Projekten, die aus vielen verschiedenen Dateien mit Quellcode bestehen, automatisiert alle Arbeitsschritte (Übersetzung, Linken, Dateien kopieren etc.) zu steuern, bis hin zum fertigen, ausführbaren Programm. make ist jedoch so flexibel ausgelegt, dass es auch beliebige andere Aufgaben steuern kann, bei denen die zeitliche Abhängigkeit von Dateien eine Rolle spielt.  
Das Hilfsprogramm make ist Teil des POSIX-Standards, dessen gegenwärtige Bezeichnung IEEE Std 1003.1, 2008 Edition lautet (äquivalent dazu Single UNIX Specification V3, SUSv3).  

Quelle: [https://de.wikipedia.org/wiki/Make](https://de.wikipedia.org/wiki/Make)

## Syntax  

Ziel: Voraussetzung1, ... , Voraussetzung n  
[echter Tabulator] Befehl 1  
[echter Tabulator] ...  
[echter Tabulator] Befehl n  

## Aufruf  

Eine bereits erstellte Makefile kann man mit dem befehl make aufrufen. Vor durchlauf des Vorganks kontrolliert das Tool den Zeitstempel der Dateien. Dateien die sich nicht verändert haben werden nicht berücksichtigt. Will man das eine unveränderte Datei trodzdem berücksichtigt wird, kann man ihren Zeitstempel mit dem Befehl touch aktualisieren.

## Erste Aufgabenstellung  

Ein Programm das eine Led auf unserem Atmega328p blinken lässt, soll mit dem tool make übersetzt werden.

# Quelltext  

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






