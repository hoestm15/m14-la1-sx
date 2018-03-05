# Protokoll 3: Microcontroller
Name: Patrick Schuster
Klasse: 4AHME  
Gruppe: 3    
Anwesend: Reinbacher, Ruffenacht, Sackl, Sackl, Sammer, Schmuck, Schuster  
Abwesend: keiner

## Wiederholung der 2. Einheit
Zu Beginn der Stunde haben wir die einzelnen Funktionen des Prozessorfensters in Atmel Studio, die CPU Register und dissambly wiederholt.  
### CPU-Register
Register | Verwendung
--- | ---
R1 | hat immer den Wert 0x00  
R8 - R25 | für Parameter und Rückgabewerte  
R26 & R27 | X-register  
R28 & R29 | Y-Register  
R30 & R31 | Z-Register  

[Protokoll der 2. Einheit](https://github.com/HTLMechatronics/m14-la1-sx/blob/suspam14/suspam14/Protokoll2.md)

## deklarieren, definieren und initialisieren
* **deklarieren** Es wird eine Variable benannt und dem Compiler bekannt gegeben.
* **definieren** Es wird der Variable ein Speicherbereich zugewiesen
* **initialisieren** Es wird der Variable ein initialer Anfangswert zugewiesen

12: {  
00000040 cf.93                PUSH R28		Push register on stack  
00000041 df.93                PUSH R29		Push register on stack   
>Pushed Register vom Stack
>R26 bis R31 dürfen bei Funktionsaufruf nicht verändert werden  

00000042 1f.92                PUSH R1		Push register on stack  
>erhöht Stackpointer um 1 -> definition von Variable  

00000043 cd.b7                IN R28,0x3D		In from I/O location  
00000044 de.b7                IN R29,0x3E		In from I/O location  
>Lädt Stackpointer in Y-Register

14: 	x=10+23;
00000045 81.e2                LDI R24,0x21		Load immediate 
00000046 89.83                STD Y+1,R24		Store indirect with displacement 
>wegen volatile  

15: 	return x;
00000047 89.81                LDD R24,Y+1		Load indirect with displacement 

    16: }
00000048 90.e0                LDI R25,0x00		Load immediate 
00000049 0f.90                POP R0		Pop register from stack 
0000004A df.91                POP R29		Pop register from stack 
0000004B cf.91                POP R28		Pop register from stack 
0000004C 08.95                RET 		Subroutine return 

```
int main(void)
{
	volatile unsigned char a=10;  
	volatile unsigned char b=20;  
	volatile int e=a+b;  
	return e;  
}
```

12: {
00000040 cf.93                PUSH R28		Push register on stack  
00000041 df.93                PUSH R29		Push register on stack  
00000042 00.d0                RCALL PC+0x0001		Relative call subroutine  
00000043 00.d0                RCALL PC+0x0001		Relative call subroutine  
>Macht Platz am Stack  

00000044 cd.b7                IN R28,0x3D		In from I/O location  
00000045 de.b7                IN R29,0x3E		In from I/O location  
>Y=SP  
    13: 	volatile unsigned char a=10;  
00000046 8a.e0                LDI R24,0x0A		Load immediate   
00000047 89.83                STD Y+1,R24		Store indirect with displacement  
    14: 	volatile unsigned char b=20;
00000048 84.e1                LDI R24,0x14		Load immediate  
00000049 8a.83                STD Y+2,R24		Store indirect with displacement  
    15: 	volatile int e=a+b;
0000004A 29.81                LDD R18,Y+1		Load indirect with displacement  
0000004B 8a.81                LDD R24,Y+2		Load indirect with displacement  
0000004C 90.e0                LDI R25,0x00		Load immediate  

0000004D 82.0f                ADD R24,R18		Add without carry  
0000004E 91.1d                ADC R25,R1		Add with carry  
>R18 + R24 = R25  

0000004F 9c.83                STD Y+4,R25		Store indirect with displacement  
00000050 8b.83                STD Y+3,R24		Store indirect with displacement  
>speichert R25 am Stack 

    16: 	return e;
00000051 8b.81                LDD R24,Y+3		Load indirect with displacement  
00000052 9c.81                LDD R25,Y+4		Load indirect with displacement  
    17: }
00000053 0f.90                POP R0		Pop register from stack 
00000054 0f.90                POP R0		Pop register from stack 
00000055 0f.90                POP R0		Pop register from stack 
00000056 0f.90                POP R0		Pop register from stack 
00000057 df.91                POP R29		Pop register from stack 
00000058 cf.91                POP R28		Pop register from stack
> Leert Stack


Addition dauert 46 Takte  
Multiplikation dauert 47 Takte  
Division dauert 123 Takte  
32 bit + 32 bit dauert 92 Takte  
32 bit * 32 bit dauert 165 Takte  
32 bit / 32 bit dauert 701 Takte  

float + float dauert 911 Takte  
float * float dauert 1763 Takte  
float / float dauert 1380 Takte  

double + double dauert 911  
double * double dauert 1763  
double / double dauert 1380  
double dauert gleich lang wie float, weil bei einem avr µc statt double nur float verwendet wird
```
int main(void)
{
	unsigned char i;
	volatile int x=0;
	for(i=0;i<10;i++)
	{
		x+=10;
	}
	return 0;
}
```
    17: 		x+=10;
00000048 89.81                LDD R24,Y+1		Load indirect with displacement 
00000049 9a.81                LDD R25,Y+2		Load indirect with displacement 
0000004A 0a.96                ADIW R24,0x0A		Add immediate to word 
0000004B 9a.83                STD Y+2,R25		Store indirect with displacement 
0000004C 89.83                STD Y+1,R24		Store indirect with displacement 
0000004D 21.50                SUBI R18,0x01		Subtract immediate 
    15: 	for(i=0;i<10;i++)
0000004E c9.f7                BRNE PC-0x06		Branch if not equal 
