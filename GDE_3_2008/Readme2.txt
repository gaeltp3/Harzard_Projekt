//GDE3_3
1.	Abgebrochene Zeichenaktion behoben (z.B. IBM Notebook)
2.	Die Applikation muss jetzt mit dem RUN Button gestartet werden.
	Es gibt zus�tzlich eine Funktion StopProcess(), die in die Benutzerapplikation eingebaut werden kann.
	(z.B. Einleseschleife) 
	Wird auf den Stop Button gedr�ckt wird ein Flag gesetzt, das im StopProzess abgefragt wird.
	Dann gibt StopProcess() eine 1 zur�ck sonst 0. An die Abfrage kann dann ein break geh�ngt werden,
	um die laufende Aktion zu beenden.
3.  Der Thread, der den Benutzerprozess enth�lt, wird jetzt in der Regel sauber angehalten.
4.	Die Ausgabe kann in eine bmp Datei gespeichert und auch wieder eingelesen werden.
	Paint kann die so erzeugte Datei ebenfalls darstellen.
