# Labor KW50  
# 12.12.2017  

## Makefiles  
### Theorie  
Bei der C-Prpgrammierung verwendet man normalerweise für die Übersetzung des Programs eine **IDE(Integrated Development Environment)** wie zum Beispiel **Codeblocks** oder **Netbeans**. Diese IDE's greifen aber auch auf das Tool **make** zurück.  

Wird **make** in der Konsole aufgerufen, so wird eine Steuerdatei names **Makefile** ausgeführt.  
Bei richtiger Einstellung des **Makefile** wird nur das Nötigste gemacht und schon abgeschlossene Teile weggelassen.
In der Datei ** Makefile** befinden sich die relevanten Informationen für eine Übersetzung. 

**Zum Beispiel:**  

* was ist das Ziel der Übersetzung?  
* aus welchen Dateien (Files) besteht das Projekt?  
* welche Abhängigkeiten zwischen den Dateien sind gegegeben?  
* welche Tools (Compiler, Linker, ...) werden wie und zu welchem Zeitpunkt aufgerufen?   
 
 ### Schitte einer C-Übersetzung  
 
 **1.Schritt Compilieren**  
 Für unseren µC wird der GNU-Compiler **avr-gcc** verwendet.  
 Danach entsteht eine Datei mit der Endung **.o**
 Dazu benötigt man den Befehl   
 ```
 avr-gcc -mmcu=atmega328p -Os -c main.c
 ```  
 * mit **-mmcu** wird der µC Typ festgelegt  
 *  **-c** ist das es nur compiliert wird   
 
 **2.Schritt Linken**  
 Nach dem Compilieren ist der nächste Schritt **Linken** 
 Danach entsteht eine Datei mit der Endung **.elf**
 Dazu benötigt man den Befehl    
```
 avr-gcc -mmcu=atmega328p -Os -o main.elf main.o
 ```  
 **3.Schritt Erzeugen einer Intel Hex-Datei**  
 Von der **.elf** Datei entsteht eine **.hex**  Datei mit dem Befehl  
 ```
  avr-objcopy -O ihex main.elf main.hex
 ```    
 
 Als Übung machten wir in der Laboreinheit ein Beispiel. Dieses Beispiel compilierten, linkten und spielten das fertige Program auf den µC mit dem Befehl **make**.  
 
 **Makefile der Einheit:**
 ```  
 flash: main.hex bootloader.hex
        avrdude -c usbasp -p atmega328p -e -U flash:w:main.hex:i -U flash:w:boo$
        #avrdude -c usbasp -p atmega328p  -U flash:w:bootloader.hex:i


main.hex: main.elf
        avr-objcopy -O ihex main.elf main.hex

main.elf: main.o
        avr-gcc -mmcu=atmega328p -Os -o main.elf main.o

main.o: main.c

        avr-gcc -mmcu=atmega328p -Os -c main.c
clean: 
        -rm main.o
        -rm main.elf
        -rm main.hex
 ```
 **C-Quelltext**  
 ```  
 #define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main()
{

        DDRB |=(1 << PB5);
        while(1)
        {
                PORTB ^= (1 <<PB5);
                _delay_ms(200);
        }

        return 0;
}
```  
