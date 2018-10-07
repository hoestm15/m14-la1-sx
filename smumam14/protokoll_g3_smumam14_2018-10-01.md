# Laborprotokoll  
Erste Einheit am 24. Sept. 2018  
Martin Schmuck  
5AHME  
Gruppe 3

Automatisierungslabor HTL Kaindorf  
Anwesend: Reinbacher, Ruffenacht, Sackl M., Sackl R., Sammer, Schmuck, Schuster  
Abwesend: niemand  

## Thema der Einheit: TypeScript mit Visual Studio Code
________

#### Unterschiede in der Realisierung eines Servers zwischen Java und Node.js
In Java gibt es beispielsweise Klassen wie ServerSocket, welche fertig ausprogrammiert sind und als Bibliotheken eingebunden und verwendet werden können. Dies erleichtert die Arbeit beim Erstellen eines Servers in dieser Sprache erheblich. Bei Node.js als Plattform bzw. TypeScript als Sprache gibt es zwar die Klassen http und https, diese sind jedoch unbequem in der Handhabung. Deshalb verwenden wir das Tool __Express__. Dieses Tool bietet eine komfortabele Möglichkeit, die beiden Protokolle zu verwenden. Dabei muss es jedoch sowohl am Entwicklungsrechner als auch am Zielsystem installiert sein, weshalb bei der Installation von diesem Tool die Option `save`und nicht `save-dev` angegeben werden muss, was eine entsprechende Eintragung in die Datei `package.json` im Abschnitt Dependencies bewirkt.  
Siehe dazu das [Protokoll der letzten Einheit](/smumam14/protokoll_g3_smumam14_2018-09-24.md#anlegen-eines-typescript-projektes).  

#### Visual Studio Code  
Dabei handelt es sich um eine freie IDE, welche von Microsoft angeboten wird ([MIT-Lizenz](https://de.wikipedia.org/wiki/MIT-Lizenz)). Diese wird in der Schweiz entwickelt und hat, anders als wir zuerst vermuteten, mit ihrer Namensschwester "Visual Studio"  nicht wirklich viel gemeinsam. Dies fällt allein schon beim ersten Anblick auf, der sich wie folgt darbietet:   
![Programmstart](/resources/scrsht1.png)


