#include <stdio.h>
#include <msp430.h>

// Morse kodu dönüştürücü devresi
// Switchler P1.0-P1.3 pinlerine, grafik ekran P2.0-P2.7 pinlerine, buzzer P3.0 pinine bağlanmıştır.

// Morse kodu tablosu
char* morse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

// Girilen morse kodunu tutan dizi
char input[16];

// Çevrilen harf veya rakamı tutan değişken
char output;

// Switch durumlarını tutan değişkenler
int state1, state2, state3, state4;

// Switch durumlarını okuyan fonksiyon
void read_switches() {
  // Switch durumlarını P1 portundan oku
  state1 = P1 & 0x01; // P1.0
  state2 = P1 & 0x02; // P1.1
  state3 = P1 & 0x04; // P1.2
  state4 = P1 & 0x08; // P1.3
}

// Grafik ekranı güncelleyen fonksiyon
void update_display() {
  // Grafik ekranı temizle
  P2 = 0x00;
  // Çevrilen harf veya rakamı grafik ekranına yaz
  P2 = output;
}

// Buzzer'ı belirli bir süre çalıştıran fonksiyon
void beep(int duration) {
  // Buzzer'ı aç
  P3 |= 0x01;
  // Belirli bir süre bekle
  __delay_cycles(duration * 1000);
  // Buzzer'ı kapat
  P3 &= 0xFE;
}

// Morse kodunu buzzer ile duyuran fonksiyon
void announce_morse(char* code) {
  // Mors kodundaki her karakter için
  for (int i = 0; i < strlen(code); i++) {
    // Eğer karakter nokta ise
    if (code[i] == '.') {
      // Buzzer'ı 200 ms çalıştır
      beep(200);
    }
    // Eğer karakter çizgi ise
    else if (code[i] == '-') {
      // Buzzer'ı 600 ms çalıştır
      beep(600);
    }
    // Buzzer'ı kapat ve 200 ms bekle
    P3 &= 0xFE;
    __delay_cycles(200ı temizle
                   P2 = 0x00;
                   // Çevrilen harf veya rakamı grafik ekranına yaz
                   P2 = output;
                 }
 * 1000);
  }
  // Mors kodu bitince 600 ms bekle
  __delay_cycles(600 * 1000);
}

// Girilen morse kodunu harf veya rakama çeviren fonksiyon
void convert_from_morse(char* code) {
  // Morse kodu tablosundaki her kod için
  for (int i = 0; i < 36; i++) {
    // Eğer girilen kod tablodaki koda eşitse
    if (strcmp(code, morse[i]) == 0) {
      // Eğer kod 0-25 arasında ise
      if (i < 26) {
        // Kodu A-Z aralığına getir
        output = i + 'A';
      }
      // Eğer kod 26-35 arasında ise
      else {
        // Kodu 0-9 aralığına getir
        output = i + '0' - 26;
      }
      // Grafik ekranı güncelle
      update_display();
      // Mors kodunu buzzer ile duyur
      announce_morse(code);
      // Fonksiyondan çık
      return;
    }
  }
  // Eğer girilen kod tabloda yoksa
  // Hata mesajı göster
  output = '?';
  // Grafik ekranı güncelle
  update_display();
}

// Ana fonksiyon
void main() {
  // P1 portunu giriş olarak ayarla
  P1DIR = 0x00;
  // P2 portunu çıkış olarak ayarla
  P2DIR = 0xFF;
  // P3 portunu çıkış olarak ayarla
  P3DIR = 0xFF;
  // Buzzer'ı kapat
  P3 &= 0xFE;
  // Grafik ekranı temizle
  P2 = 0x00;
  // Girilen morse kodunu tutan diziyi boşalt
  memset(input, 0, sizeof(input));
  // Çevrilen harf veya rakamı sıfırla
  output = 0;
  // Sonsuz döngü
  while (1) {
    // Switch durumlarını oku
    read_switches();
    // Eğer P1.0 switchi açıksa
    if (state1 == 0x01) {
        printf(" put . ");
      // Nokta ekle
      strcat(input, ".");
      // Buzzer'ı 200 ms çalıştır
      beep(200);
    }
    // Eğer P1.1 switchi açıksa
    else if (state2 == 0x02) {
      // Çizgi ekle
        printf(" put - ");
        strcat(input, "-");
      // Buzzer'ı 600 ms çalıştır
      beep(600);
    }
    // Eğer P1.2 switchi açıksa
    else if (state3 == 0x04) {
        printf(" convert ");
      // Girilen morse kodunu harf veya rakama çevir
      convert_from_morse(input);
      // Girilen morse kodunu tutan diziyi boşalt
      memset(input, 0, sizeof(input));
    }
    // Eğer P1.3 switchi açıksa
    else if (state4 == 0x08) {
      // Boşluk ekle
        printf(" space");
      output = ' ';
      // Grafik ekranı güncelle
      update_display();
    }

  }
}
