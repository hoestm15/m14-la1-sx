# Labor KW02 09.01.2018

## Wiederholung  
Am Beginn der ersten Einheit schrieben wir mit eine Wiederholung über die Einheit 4 und Einheit 5.  
Die Themengebiete beim Test waren **Makefiles** und **Modbus**.  

## Java Native Interface (JNI)
> JNI ermöglicht es, native Methoden zu schreiben für Situationen, in denen es nicht möglich ist, ausschließlich Java als Programmiersprache einzusetzen. Dies ist der Fall, wenn beispielsweise die Standard-Java-Klassenbibliothek bestimmte Plattform-abhängige Features oder andere Programmbibliotheken nicht unterstützt. Weiterhin ist es per JNI möglich, eine weitere in einer anderen Programmiersprache programmierte Anwendung für Java zugreifbar zu machen. Viele Klassen der Java-Standardbibliothek basieren auf JNI, um beispielsweise die Datei-Ein- und Ausgabe oder Soundwiedergabe zu ermöglichen. Indem Java Leistungs- und Plattform-abhängige Implementierungen in die Standardbibliothek integriert, kann der Java-Programmierer und -Nutzer diese Features in sicherer und Plattform-unabhängiger Weise nutzen.  
  *Quelle: [Wikipedia, JNI](https://de.wikipedia.org/wiki/Java_Native_Interface)*  
  
Wir benötigen das JNI um eine Kommunikationsschnittstelle zwischen unserer [Java Virtual Machine](https://de.wikipedia.org/wiki/Java_Virtual_Machine) und den [seriellen Schnittstellen](https://de.wikipedia.org/wiki/Serielle_Schnittstelle) auf die unserer Betriebssystem zugreift, herzustellen. Um auf USB-Schnittstellen im Speziellen zuzugreifen wird die Schnittstelle [javax.comm](https://de.wikipedia.org/wiki/Java_Communications_API) verwendet.  
### Funktionsweise in unserem Fall
![JNI](/zitkam13/jni.PNG)
### Programmbibliotheken
In unseren *AIIT-Templates* unter Netbeans finden sich [Programmbibliotheken](https://de.wikipedia.org/wiki/Programmbibliothek) für JNI.
Jedes Betriebssystem, bzw. jede [Architektur](https://de.wikipedia.org/wiki/Rechnerarchitektur) benötigt zum Kompilieren seine/ihre eigene Bibliothek.

| Betriebssystem | Architektur | Wortbreite | Kürzel |
|:--------------:|:-----------:|:----------:|:------:|
| [Linux](https://de.wikipedia.org/wiki/Linux) | [x86](https://de.wikipedia.org/wiki/X86-Prozessor) | 32 bit | `.so` |
| [Linux](https://de.wikipedia.org/wiki/Linux) | [x86](https://de.wikipedia.org/wiki/X86-Prozessor) | 64 bit | `.so` |
| [Linux](https://de.wikipedia.org/wiki/Linux) | [ARM](https://de.wikipedia.org/wiki/ARM-Architektur) | 32 bit | `.so` |
| [Windows](https://de.wikipedia.org/wiki/Microsoft_Windows) | [x86](https://de.wikipedia.org/wiki/X86-Prozessor) | 32 bit | `.dll` |
| [Windows](https://de.wikipedia.org/wiki/Microsoft_Windows) | [x86](https://de.wikipedia.org/wiki/X86-Prozessor) | 64 bit | `.dll` |

## Programm   
Wir setzten das Program der Einheit 5 (19.12.2017) fort. Bei diesem Programm wurde die Temperatur visualisiert. Gemessen wurde diese mit dem Sure-Board und danach mit Modbus übertragen.  
Dabei programmierten wir unter anderem die Steurung der Buttons der GUI.  

**Quellcode der Buttons**  
```java
    private void updateSwingControls () {
    jcbSerialDevice.setEnabled(false);
    jbutRefresh.setEnabled(true);
    jbutConnect.setEnabled(false);
    jbutDisconnect.setEnabled(false);
    jbutSingleMeasurement.setEnabled(false);
    jbutContinousMeasurement.setEnabled(false);
    jbutStopMeasurement.setEnabled(false);
    
    if (jcbSerialDevice.getModel().getSize() > 0) {
      jcbSerialDevice.setEnabled(true);
      jbutConnect.setEnabled(true);
    }
    
    if (serialPort != null) {
      jbutConnect.setEnabled(false);
      jbutDisconnect.setEnabled(true);
      jbutRefresh.setEnabled(false);
      jcbSerialDevice.setEnabled(false);
    } else {
      jbutConnect.setEnabled(true);
      jbutDisconnect.setEnabled(false);
    }
  }

```  
**GUI des Programms**  
![Display](https://github.com/HTLMechatronics/m14-la1-sx/blob/wiemam14/wiemam14/GUI.PNG)  


## Exceptions in JAVA  
Die Klasse **Exception** wird von **Throwable** abgeleitet. Diese wiederum wird vom der Klasse Object abgelditet. Bei schweren Fehlern wir in der **JVM(Java Virtual Machine)** ein Error erzeugt, welcher zu einem Absturz des Programms führt. Alle Errors die von **JSSC** geworfen werden, ,üssen weitergeworfen werden, wenn nur Exceptions abgefangen werden. Für die Lösung dieses Problems gibt es zwei Lösungen. Entweder wird ein **Multicatch** verwendet oder es werden alle **Throwables** abgefangen. Mit beiden Varianten können **Errors** und **Exceptions** behandelt werden. 
