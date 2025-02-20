#Matrikelnummern

Hibert, Robin: 3518513

Thiemann, Julian: 3524295

# Dropbox/Video Link
    [](https://www.dropbox.com/scl/fo/i04a6hs1nnd1vp7jkf3ml/h?rlkey=uuagbehbsffmt2htgmac8aod5&dl=0)

# MCT-Projekt: Flappy Birb

Dieses Projekt ist als Prüfungsleistung für den Microcontrollertechnik Kurs im WS 23/24 entstanden. Unsere Idee war es das bekannte Spiel "Flappy Bird" auf dem Microcontroller RP-2024 darzustellen, den es als Vorraussetzung für dieses Projekt gab.
Das gesamte Projekt wurde mit einer Schnittstelle Namens "Yahal" entwickelt, welche unserem Professor Prof. Dr. Andreas Terstegge zur Verfügung gestellt
# Benutzte Schnittstellen
1. gpio_rp2040_pin
2. spi_rp2040
3. st7735s_drv
4. timer_rp2040
5. adc_rp2040_channel
# Umsetzung
Die Anwendung wird gestartet in dem die fappy.birb.cpp Datei ausgeführt wird. Diese ist im Endeffekt nur dafür das Spiel zu starten. Die Logik für dieses befindet sich in der game.cpp, wo die Bewegungen, die Kolisionen, das Visualisieren und weiteres implementiert sind.
Für alle Buchstaben und Zahlen die angezeigt werden gibt es eine Hilfsklasse CharacterDrawer.cpp.
Eine weitere Hilfsklasse ist GetColors.cpp diese ist dafür verantwortlich, das der Hintergrund geladen wird, wenn die Röhren oder der Birb sich bewegen.
#Features
Das Spiel beginnt im Hauptmenü, wo es drei Menüpunkte gibt. Der erste ist der Spielen Punkt, bei bestätigen von diesem wird das Spiel gestartet. Unter der Auswahl Score findet man eine Liste von den Top 10 erzielten Scores mit zugehörigem Namen. Das letzte ist Setting, darunter kann man den Namen und den Schwierigkeitsmodus einstellen.

# Schwierigkeitsmodi
    - Easy
    - Medium
    - Hard
    - Extreme
    - Insane
# Steuereung
    - Button S1 -> Bestätigen/Springen
    - Button S2 -> Menü Navigieren/ --

# Herausforderungen
Besonders Probleme haben die Timer bereitet, gerade wenn beide gleichzeitig, mit oder ohne callbacks auf einer recht niedrigen Frequenz liefen, kam es öfter zu Problemen. Irgendwie wirkte es auch immer sehr willkürlich, manchmal startetete der eine nicht, manchmal der andere nicht, manchmal keiner, obwohl am Programm nichts geändert wurde. 
Das Visualisieren bzw. Ersetzen von richtigen stellen, und dies auch nicht zu oft, galt es auch zu bewältigen, wenn etwas zu spät oder zu oft ersetzt wurde, konnte man starkes flackern feststellen. 
