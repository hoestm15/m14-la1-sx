# Protokoll 4: Makefiles

Das Tool make benötigt die Datei Makefile. Diese Makefile steuert den Übersetzungsvorgang.   
Die Makefile Datei ist eine gewöhnliche Textdatei.  

Datei Makefile  
Ziele:Abhängigkeit  
[Tab] Kommandos  
[Tab] Kommandos

Ziel B: Abhängigkeit  
[Tab] ...  

Bsp.:  
test1:main.o  
[Tab] gcc -o test1 main.o  
main.o:main.c  
[Tab] gcc -c main.c  


