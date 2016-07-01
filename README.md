# Kometa

Muine replacement written in QT using irrKlang sound engine and id3lib libraries.

#How to compile
Install id3lib from source
http://www.linuxfromscratch.org/blfs/view/6.3/multimedia/id3lib.html

Install irklang library see 
https://github.com/blackuprise/Kometa/blob/master/libs/irrKlang-64bit-1.5.0/readme.txt

Open Kometa.pro in the QtCreator and try to run it :}.
irklang *.so libraries must be in the same directory as kometa executable. Or copy them to /usr/lib/.

#Troubleshoot
If Kometa start but playing wierd noises that means application didn't find required *.so libraries for irklang sound library located in 

#Help needed
If someone has a experience in packaging applications for linux distributions they are welcomed to contribute in packaging the apllication. Ubuntu/Fedora etc..

