# PH_Synth   
## von Michael Pohn (415427) und Hannes Hügel (412474)
Vollständiger bespielbarer Synthesizer. Bestehend aus Sequenzer, Harmonizer, Pitchshifter und Oszilatoren mit einstellbaren Formaten

Für die vollständige Funktion des PH_Synth müssen zwei C-Externals kompiliert werden.

# C-External 1: PH_PitchPerfect
  Ein PD-Objekt zur Berechnung von Frequenzwerten für Dur-,Moll- und verminderte Dreiklänge in reiner Stimmung
  Es werden Frequenzwerte für die Dreiklänge anhand der westlicher Stufentheorie generiert.
  
  Input: Frequenzwert für die grundlegende Tonika
  
  Outputs: Frequenzwerte für Dreiklänge
  
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
    einstellbare Wellenform
    Regler zur Einstellung der Formantenbereiche
    vier Hüllkurven für die Formanten
    Regler für Geschwindigkeit des Hüllkurven-Durchlaufs
      
## Geplante Weiter-Entwicklung
-Ansteuerung der Parameter mit MIDI-Controller
