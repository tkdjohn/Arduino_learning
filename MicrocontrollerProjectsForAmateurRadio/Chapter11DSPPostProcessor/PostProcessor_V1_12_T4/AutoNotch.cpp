/*****
  Purpose:  SetAutoNotch
  Paramter list:

  Return value:  void
*****/
/*void SetAutoNotch() {
  float prob;
  float note;
  int noteFlag;
  float noteAve;
  float noteOld = 0;
  float tiny = .9;
  long xnew;
  long xave;
  Serial.println("in setAutoNotch");
  int i;


  while (1) {
    Serial.println("in While");
    if (notefreq.available()) {
      Serial.println("in if");
      //xnew = notefreq.read();
      prob = notefreq.probability();

      //if (prob > .9) {
        for (int i = 1; i < 11; i++) {
          xNotch[i] = notefreq.read();
          xave = xave + xNotch[i];
        }
        xave = xave / 10;
        xnew = notefreq.read();
        prob = notefreq.probability();
        
        if (xnew / 10 < xave / 10+50 and  xnew / 10 > xave / 10-50) {
          xNotch[1] = xnew;
        }
        for (int i = 1; 2 < 11; i++) {
          xNotch[i - 1] = xNotch[i];
        }
        notchFreq = xNotch[1];

        Notch.setNotch(0, notchFreq, 10);
        Notch.setNotch(1, notchFreq, 10);
        Notch.setNotch(2, notchFreq, 10);
        Notch.setNotch(3, notchFreq, 10);
        Serial.printf("Note: %3.2f | Probability: %.2f\n", note, prob);
        noteOld = note;
        displayNotchFilter();
      //}

    }
    displayNotchFilter();
  }
}*/
