# PH_Synth   

Videoexplanation under https://vimeo.com/518617869

## von Michael Pohn (415427) und Hannes Hügel (412474)
Vollständiger bespielbarer Synthesizer. Bestehend aus Sequenzer, Harmonizer, Pitchshifter und Oszillatoren mit einstellbaren Formaten-Envelopes.

Synthesizer aktiviert Frequenzwerte des Harmonizers, diese durchlaufen einen Pitchshift (einfache Division) und werden an separate Oszillatoren geleitet.
(Vgl. PH_Synth.Pdf)

Für die vollständige Funktion des PH_Synth müssen zwei C-Externals kompiliert werden.

# C-External 1: PH_PitchPerfect
  Ein PD-Objekt zur Berechnung von Frequenzwerten für Dur-,Moll- und verminderte Dreiklänge in reiner Stimmung
  Es werden Frequenzwerte für die Dreiklänge anhand der westlicher Stufentheorie generiert.
  
  Input: Frequenzwert für die grundlegende Tonika
  
  Outputs: Frequenzwerte für Dreiklänge in Grundstellung
  
    I   -Stufe: Dur-Dreiklang
    ii  -Stufe: Moll-Dreiklang
    iii -Stufe: Moll-Dreiklang
    IV  -Stufe: Dur-Dreiklang
    V   -Stufe: Dur-Dreiklang
    vi  -Stufe: Moll-Dreiklang
    vii0-Stufe: verminderter Dreiklang
  
  Die Frequenzwerte werden in Bündeln von 3 Werten untereinander in PD-Zahlenboxen geschrieben
  
# C-External 2: PH_Formant_OSC

Ein PD-Objekt für die Erzeugung eines zeitlich veränderlichen Tons.

Input: Frequenzwert

Output: Signalstream

  Parameter:
  
    Anzahl der Obertöne 
    Einstellbare Wellenform
    Regler zur Einstellung der Formantenbereiche
    Vier Hüllkurven für die Formanten
    Regler für Geschwindigkeit des Hüllkurven-Durchlaufs
      
## Geplante Weiter-Entwicklung
### PD-Patch
    Ansteuerung der Parameter mit MIDI-Controller (done)
    Hinzufügen eines Halls
    
### PH_PitchPerfect
    Implementierung einer Logik um Akkord-Inversionen miteinzubeziehen
    Erweiterung um einen weiteren Akkordton (Vierklänge)
    
### PH_Formant_OSC
    Envelopedurchlaufzeit für jeden einzelenen Formantenbereich einstellbar machen
    Voreinstellbare Wellenformen (Rechteck, Sägezahn, Dreieck)
