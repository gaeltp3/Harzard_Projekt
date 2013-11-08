================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : GDE_3 Projekt�bersicht
================================================================================

Der Anwendungs-Assistent hat diese GDE_3-Anwendung erstellt. 
Diese Anwendung zeigt die prinzipielle Anwendung der Microsoft Foundation Classes 
und dient als Ausgangspunkt f�r die Erstellung Ihrer eigenen Anwendungen.

Diese Datei enth�lt die Zusammenfassung der Bestandteile aller Dateien, die 
Ihre GDE_3-Anwendung bilden.

GDE_3.vcproj
    Dies ist die Hauptprojektdatei f�r VC++-Projekte, die vom Anwendungs-Assistenten 
    erstellt wird. Sie enth�lt Informationen �ber die Version von Visual C++, mit der
    die Datei generiert wurde, �ber die Plattformen, Konfigurationen und Projektfeatures,
    die mit dem Anwendungs-Assistenten ausgew�hlt wurden.

GDE_3.h
    Hierbei handelt es sich um die Haupt-Headerdatei der Anwendung. Diese enth�lt 
    andere projektspezifische Header (einschlie�lich Resource.h) und deklariert die
    CGDE_3App-Anwendungsklasse.

GDE_3.cpp
    Hierbei handelt es sich um die Haupt-Quellcodedatei der Anwendung. Diese enth�lt die
    Anwendungsklasse CGDE_3App.

GDE_3.rc
    Hierbei handelt es sich um eine Auflistung aller Ressourcen von Microsoft Windows, die 
    vom Programm verwendet werden. Sie enth�lt die Symbole, Bitmaps und Cursors, die im 
    Unterverzeichnis RES gespeichert sind. Diese Datei l�sst sich direkt in Microsoft
    Visual C++ bearbeiten. Ihre Projektressourcen befinden sich in 1031.

res\GDE_3.ico
    Dies ist eine Symboldatei, die als Symbol f�r die Anwendung verwendet wird. Dieses 
    Symbol wird durch die Haupt-Ressourcendatei GDE_3.rc eingebunden.

res\GDE_3.rc2
    Diese Datei enth�lt Ressourcen, die nicht von Microsoft Visual C++ bearbeitet wurden.
    In dieser Datei werden alle Ressourcen gespeichert, die vom Ressourcen-Editor nicht bearbeitet 
    werden k�nnen.
/////////////////////////////////////////////////////////////////////////////

F�r das Hauptfenster:
    Das Projekt enth�lt eine MFC-Standardschnittstelle.
MainFrm.h, MainFrm.cpp
    Diese Dateien enthalten die Frame-Klasse CMainFrame, die von
    CFrameWnd abgeleitet wird und steuert alle SDI-Framefeatures.
res\Toolbar.bmp
    Diese Bitmap-Datei wird zum Erstellen unterteilter Bilder f�r die Symbolleiste verwendet.
    Die erste Symbol- und Statusleiste wird in der Klasse CMainFrame
    erstellt. Bearbeiten Sie diese Bitmap der Symbolleiste mit dem Ressourcen-Editor, und
    aktualisieren Sie das Array IDR_MAINFRAME TOOLBAR in GDE_3.rc, um 
    Schaltfl�chen f�r die Symbolleiste hinzuzuf�gen.
/////////////////////////////////////////////////////////////////////////////

Der Anwendungs-Assistent erstellt einen Dokumenttyp und eine Ansicht:

GDE_3Doc.h, GDE_3Doc.cpp - das Dokument
    Diese Dateien enthalten die Klasse CGDE_3Doc.  Bearbeiten Sie diese Dateien,
    um Ihre speziellen Dokumentdaten hinzuzuf�gen und das Speichern und Laden von 
    Dateien zu implementieren (mit CGDE_3Doc::Serialize).
GDE_3View.h, GDE_3View.cpp - die Ansicht des Dokuments
    Diese Dateien enthalten die Klasse CGDE_3View.
    CGDE_3View-Objekte werden verwendet, um CGDE_3Doc-Objekte anzuzeigen.
/////////////////////////////////////////////////////////////////////////////

Weitere Features:

ActiveX-Steuerelemente
    Die Anwendung unterst�tzt die Verwendung von ActiveX-Steuerelementen.

Unterst�tzung f�r das Drucken und die Seitenansicht
    Der Anwendungs-Assistent hat den Code zum Verarbeiten der Befehle "Drucken", "Seite einrichten" und 
    "Seitenansicht" durch Aufrufen der Memberfuntkionen in der CView-Klasse der MFC-Bibliothek generiert.
/////////////////////////////////////////////////////////////////////////////

Weitere Standarddateien:

StdAfx.h, StdAfx.cpp
    Mit diesen Dateien werden vorkompilierte Headerdateien (PCH) mit der Bezeichnung
    GDE_3.pch und eine vorkompilierte Typdatei mit der Bezeichnung 
    StdAfx.obj erstellt.

Resource.h
    Dies ist die Standard-Headerdatei, die neue Ressourcen-IDs definiert.
    Microsoft Visual C++ liest und aktualisiert diese Datei.

/////////////////////////////////////////////////////////////////////////////

Weitere Hinweise:

Der Anwendungs-Assistent verwendet "TODO:", um die Stellen anzuzeigen, 
an denen Sie Erweiterungen oder Anpassungen vornehmen k�nnen.

Wenn Ihre Anwendung die MFC in einer gemeinsam genutzten DLL verwendet und 
eine andere als die aktuell auf dem Betriebssystem eingestellte Sprache verwendet, muss 
die entsprechend lokalisierte Ressource MFC70XXX.DLL von der Microsoft Visual C++ CD-ROM 
in das Verzeichnis system oder system32 kopiert und in MFCLOC.DLL umbenannt werden  
("XXX" steht f�r die Abk�rzung der Sprache. So enth�lt beispielsweise MFC70DEU.DLL die ins Deutsche 
�bersetzten Ressourcen.)  Anderenfalls werden einige Oberfl�chenelemente Ihrer Anwendung 
in der Sprache des Betriebssystems angezeigt.

/////////////////////////////////////////////////////////////////////////////
