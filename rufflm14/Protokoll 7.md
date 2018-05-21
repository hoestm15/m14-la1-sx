# **7. Laborprotokoll** 

*von Florian Ruffenacht*

Datum: 15.05.2017 (Gruppe 3)

Ort: AUT-Labor

Lehrkraft: SX

Abwesend: -

## Wiederholung der letzten Einheit(en)

Zu Beginn der Einheit wiederholten wir ausführlich die den bereits besprochenen Stoff zum Projekt Temperaturmessung mittels Mikroprozessor. Zum Beispiel wurde uns der Hardwareaufbau wieder ins Gedächtnis gerufen. 

[Link zum Protokoll der 5.Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/rufflm14/rufflm14/Protokoll_5.md)

## Programmieren des SingleMeasurementWorkers

Der SingleMeasurementWorker ist eine JAVAl-Klasse, die in einem eigenen Thread die Temperatur über die serielle Schnitstelle einmalig abfragen soll. Ihm wird im Konstruktor die serielle Schnitstelle (serialPort) übergeben. Die Modbus-Anfrage besteht aus folgenden 8 Bytes: 2,4,0,0x30,0,1,0x31,0xf6.

Nach einer Wartezeit von 100ms wird die Antwort abgefragt und auf Herz und Nieren geprüft. Gegebenenfalls wird eine Exception geworfen. Sie soll aus 9 Bytes bestehen und die Werte der Temperaturmessung befinden sich an der 3. und der 4. Stelle. Löst die Antwort keine Exception aus, wird die Temperatur in Grad ausgerechet und zurückgegeben.

