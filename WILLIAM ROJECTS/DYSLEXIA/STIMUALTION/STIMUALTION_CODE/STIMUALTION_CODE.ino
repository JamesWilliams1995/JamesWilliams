#include "initial.h"
#include "mic_freqency.h"
#include "lcd.h"
char CHANGE_DATA;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  freq_init();
  for (int i = 0; i <= 14; i++) {
    pinMode(LED[i], OUTPUT);
    pinMode(A0, INPUT);
    digitalWrite(LED[i], LOW);
  }
  lcd.setCursor(0, 0);
  lcd.print("    DYSLEXIA    ");
  lcd.setCursor(0, 1);
  lcd.print("       *_*      ");

}

void loop() {
  // put your main code here, to run repeatedly:


  switch (data) {

    case'A':
      data = ' ';
      lcd.clear();
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 9; i++) {
        digitalWrite(A[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq----a--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..A");
        if (peak >= 130 && peak < 148) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'B';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'B':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 9; i ++ ) {
        digitalWrite(B[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq ---b---data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..B");
        if (peak >= 148 && peak < 167) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'C';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'C':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(C[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --c--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..C");
        if (peak >= 167 && peak < 185) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'D';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'D':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 9; i++) {
        digitalWrite(D[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --d--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..D");
        if (peak >= 185 && peak < 206) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'E';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'E':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 10; i++) {
        digitalWrite(E[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --e--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..E");
        if (peak >= 206 && peak < 226) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'F';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'F':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(F[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --f--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..F");
        if (peak >= 226 && peak < 245) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'G';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'G':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 11; i++) {
        digitalWrite(G[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --g--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..G");
        if (peak >= 245 && peak < 264) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'H';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'H':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 10; i++) {
        digitalWrite(H[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --h--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..H");
        if (peak >= 264 && peak < 285) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'I';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'I':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(I[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --i--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..I");
        if (peak >= 285 && peak < 305) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'J';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'J':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(J[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --j--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..J");
        if (peak >= 305 && peak < 323) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'K';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'K':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 9; i++) {
        digitalWrite(K[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --k--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..K");
        if (peak >= 323 && peak < 342) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'L';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'L':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(L[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --l--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..L");
        if (peak >= 342 && peak < 362) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'M';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'M':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 10; i++) {
        digitalWrite(M[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --m--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..M");
        if (peak >= 362 && peak < 383) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'N';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'N':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(N[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --n--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..N");
        if (peak >= 383 && peak < 402) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'O';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'O':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 7; i++) {
        digitalWrite(O[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --o--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..O");
        if (peak >= 402 && peak < 420) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'P';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'P':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 9; i++) {
        digitalWrite(P[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --p--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..P");
        if (peak >= 420 && peak < 440) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'Q';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'Q':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(Q[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --q--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..Q");
        if (peak >= 440 && peak < 461) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'R';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'R':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 10; i++) {
        digitalWrite(R[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --r--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..R");
        if (peak >= 461 && peak < 481) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'S';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'S':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(S[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --s--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..S");
        if (peak >= 481 && peak < 498) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'T';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'T':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(T[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --t--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..T");
        if (peak >= 498 && peak < 519) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'U';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'U':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 10; i++) {
        digitalWrite(U[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --u--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..U");
        if (peak >= 519 && peak < 539) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'V';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'V':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(V[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --v--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..V");
        if (peak > 539 && peak < 559) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'W';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'W':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 10; i++) {
        digitalWrite(W[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --w--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..W");
        if (peak >= 559 && peak < 578) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'X';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'X':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(X[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --x--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..X");
        if (peak >= 578 && peak < 597) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'Y';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'Y':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(Y[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --y--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..Y");
        if (peak >= 597 && peak < 618) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'Z';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'Z':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 8; i++) {
        digitalWrite(Z[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --z--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..Z");
        if (peak >= 618 && peak < 638) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = 'A';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'0':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 7; i++) {
        digitalWrite(N0[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --zero--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..0");
        if (peak >= 638 && peak < 656) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '1';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'1':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 7; i++) {
        digitalWrite(N1[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --one--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..1");
        if (peak >= 656 && peak < 675) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '2';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'2':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 7; i++) {
        digitalWrite(N2[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --two--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..2");
        if (peak >= 675 && peak < 695) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '3';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'3':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(N3[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --three--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..3");
        if (peak >= 695 && peak < 716) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '4';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'4':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 7; i++) {
        digitalWrite(N4[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --four--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..4");
        if (peak >= 716 && peak < 735) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '5';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'5':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 9; i++) {
        digitalWrite(N5[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --five--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..5");
        if (peak >= 735 && peak < 754) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '6';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'6':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(N6[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --six--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..6");
        if (peak >= 754 && peak < 774) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '7';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'7':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 7; i++) {
        digitalWrite(N7[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --seven--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..7");
        if (peak >= 774 && peak < 794) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '8';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'8':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(N8[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --eight--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..8");
        if (peak >= 794 && peak < 813) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '9';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;

    case'9':
      lcd.clear();
      data = ' ';
      for (int i = 0; i <= 14; i++) {
        digitalWrite(LED[i], LOW);
      }
      delay(100);
      for (int i = 0; i <= 6; i++) {
        digitalWrite(N9[i], HIGH);
        delay(10);
      }
      temp = 1;
      while (temp == 1) {
        freq_read();
        Serial.println(peak);
        Serial.println("waiting for freq --nine--- data...:");
        lcd.setCursor(0, 0);
        lcd.print("F:");
        lcd.print(peak);
        lcd.setCursor(6, 0);
        lcd.print("wtg FrQ..9");
        if (peak >= 813 && peak < 832) {
          lcd.setCursor(0, 1);
          lcd.print("FREQENCY MATCHED");
          data = '0';
          break;
        }
        else if (Serial.available() > 0) {
          data = Serial.read();
          break;
        }
        delay(100);
      }
      break;
  }
  delay(100);
}


void serialEvent() {
  while (Serial.available() > 0) {
    CHANGE_DATA = Serial.read();
    Serial.print(CHANGE_DATA);
    switch (CHANGE_DATA) {
      case'A':
        data = 'A';
        break;

      case'B':
        data = 'B';
        break;

      case'C':
        data = 'C';
        break;

      case'D':
        data = 'D';
        break;

      case'E':
        data = 'E';
        break;

      case'F':
        data = 'F';
        break;

      case'G':
        data = 'G';
        break;

      case'H':
        data = 'H';
        break;

      case'I':
        data = 'I';
        break;

      case'J':
        data = 'J';
        break;

      case'K':
        data = 'K';
        break;

      case'L':
        data = 'L';
        break;

      case'M':
        data = 'M';
        break;

      case'N':
        data = 'N';
        break;

      case'O':
        data = 'O';
        break;

      case'P':
        data = 'P';
        break;

      case'Q':
        data = 'Q';
        break;

      case'R':
        data = 'R';
        break;

      case'S':
        data = 'S';
        break;

      case'T':
        data = 'T';
        break;

      case'U':
        data = 'U';
        break;

      case'V':
        data = 'V';
        break;

      case'W':
        data = 'W';
        break;

      case'X':
        data = 'X';
        break;

      case'Y':
        data = 'Y';
        break;

      case'Z':
        data = 'Z';
        break;

      case'0':
        data = '0';
        break;

      case'1':
        data = '1';
        break;

      case'2':
        data = '2';
        break;

      case'3':
        data = '3';
        break;

      case'4':
        data = '4';
        break;

      case'5':
        data = '5';
        break;

      case'6':
        data = '6';
        break;

      case'7':
        data = '7';
        break;

      case'8':
        data = '8';
        break;

      case'9':
        data = '9';
        break;
    }
  }
}
