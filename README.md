# PH_Synth   
## von Michael Pohn und Hannes Hügel 
Ist ein vollständiger bespielbarer Synthesizer. Bestehend aus Sequenzer, Harmonizer, Pitchshifter und Oszilatoren

Für die vollständige Funktion des PH_Synth müssen zwei C-Externals kompiliert werden.

# C-External 1: PH_PitchPerfect
  Ein PD-Objekt zur Berechnung von Frequenzwerten für Dur-,Moll- und verminderte Dreiklänge in reiner Stimmung
  Es werden Frequenzwerte für die Dreiklänge anhand der westlicher Stufentheorie generiert.
  
  Input: Frequenzwert für die grundlegende Tonika
  
  Outputs: Frequenzwerte 
    I   -Stufe: Dur-Dreiklang
    ii  -Stufe: Moll-Dreiklang
    iii -Stufe: Moll-Dreiklang
    IV  -Stufe: Dur-Dreiklang
    V   -Stufe: Dur-Dreiklang
    vi  -Stufe: Moll-Dreiklang
    vii0-Stufe: verminderter Dreiklang
  
  Die Frequenzwerte werden in Bündeln von 3 Werten untereinander in PD-Zahlenboxen geschrieben
  
# C-External 2: PH_Formanten_OSC
  Ein PD-Objekt für die Erzeugung eines zeitlich veränderlichen Tons

