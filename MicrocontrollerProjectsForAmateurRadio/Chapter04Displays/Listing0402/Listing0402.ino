/*
                              LICENSE AGREEMENT

  This program source code and its associated hardware design at subject to the GNU General Public License version 2,
  https://opensource.org/licenses/GPL-2.0
  with the following additional conditions:
  1. Any commercial use of the hardware or software is prohibited without express, written, permission of the authors.
  2. This entire comment, unaltered, must appear at the top of the primary source file. In the Arduino IDE environemnt, this comment must
  appear at the top of the INO file that contains setup() and loop(). In any other environmentm, it must appear in the file containing
  main().
  3. This notice must appear in any derivative work, regardless of language used.

*/
/*****
  Purpose: A simple ISR for the rotary encoder. 

  Paramter list:
    void

  Return value:
    void
*****/
void interruptServiceRoutine()
{
  if (digitalRead(ENCODER1PINA))
    state = digitalRead(ENCODER1PINB);
  else
    state = !digitalRead(ENCODER1PINB);
  fired = true;
}
