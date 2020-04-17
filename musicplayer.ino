#include <Arduboy2.h>
#include <ArduboyTones.h>
#define MAX 8
#define MAX_IMPLEMENTED 3
#define STATE_SELECTION 0
#define STATE_PLAYING 1

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

int sel = 0;
int cur_state = 0;
int old_state = 0;
int state = STATE_SELECTION;
int f = 0;
int t = 0;
char buf[6];

const char *titles[MAX] = {
  "Little Star",
  "KyouNoHiHaSaYouNaRa",
  "MiraiNoBokura"
};

const uint16_t little_star[] PROGMEM= {
  NOTE_C5, 500,
  NOTE_C5, 500,
  NOTE_G5, 500,
  NOTE_G5, 500,
  NOTE_A5, 500,
  NOTE_A5, 500,
  NOTE_G5, 1000,
  NOTE_F5, 500,
  NOTE_F5, 500,
  NOTE_E5, 500,
  NOTE_E5, 500,
  NOTE_D5, 500,
  NOTE_D5, 500,
  NOTE_C5, 1000,
  NOTE_G5, 500,
  NOTE_G5, 500,
  NOTE_F5, 500,
  NOTE_F5, 500,
  NOTE_E5, 500,
  NOTE_E5, 500,
  NOTE_D5, 1000,
  NOTE_G5, 500,
  NOTE_G5, 500,
  NOTE_F5, 500,
  NOTE_F5, 500,
  NOTE_E5, 500,
  NOTE_E5, 500,
  NOTE_D5, 1000,
  NOTE_C5, 500,
  NOTE_C5, 500,
  NOTE_G5, 500,
  NOTE_G5, 500,
  NOTE_A5, 500,
  NOTE_A5, 500,
  NOTE_G5, 1000,
  NOTE_F5, 500,
  NOTE_F5, 500,
  NOTE_E5, 500,
  NOTE_E5, 500,
  NOTE_D5, 500,
  NOTE_D5, 500,
  NOTE_C5, 1000,
  TONES_END
};

const uint16_t kyou[] PROGMEM = {
  NOTE_G5, 1050,
  NOTE_E5, 350,
  NOTE_F5, 350,
  NOTE_G5, 350,
  NOTE_A5, 1400,
  NOTE_A5, 350,
  NOTE_A5, 350,
  NOTE_G5, 1050,
  NOTE_G5, 350,
  NOTE_G5, 350,
  NOTE_E5, 350,
  NOTE_E5, 2100,
  NOTE_A4, 1050,
  NOTE_B4, 350,
  NOTE_C5, 350,
  NOTE_CS5, 350,
  NOTE_D5, 1400,
  NOTE_A4, 350,
  NOTE_E5, 350,
  NOTE_D5, 4200,
  NOTE_G5, 1050,
  NOTE_E5, 350,
  NOTE_F5, 350,
  NOTE_G5, 350,
  NOTE_A5, 1400,
  NOTE_A5, 350,
  NOTE_A5, 350,
  NOTE_G5, 1400,
  NOTE_E5, 350,
  NOTE_D5, 350,
  NOTE_C5, 1400,
  NOTE_C5, 700,
  NOTE_D5, 1400,
  NOTE_A5, 700,
  NOTE_G5, 1400,
  NOTE_D5, 350,
  NOTE_E5, 350,
  NOTE_C5, 2500,
  TONES_END
};

const uint16_t mirai[] PROGMEM = {
  NOTE_C5, 900,
  NOTE_F5, 150,
  NOTE_F5, 750,
  NOTE_E5, 300,
  NOTE_D5, 300,
  NOTE_C5, 450,
  NOTE_G5, 150,
  NOTE_REST, 300,
  NOTE_F5, 900,
  NOTE_B4, 300,
  NOTE_C5, 300,
  NOTE_D5, 300,
  NOTE_E5, 150,
  NOTE_F5, 750,
  NOTE_A5, 600,
  NOTE_G5, 300,
  NOTE_F5, 150,
  NOTE_F5, 2550,
  NOTE_C5, 300,
  NOTE_F5, 150,
  NOTE_E5, 300, 
  NOTE_F5, 300,
  NOTE_D5, 300,
  NOTE_E5, 300,
  NOTE_F5, 300,
  NOTE_D5, 150,
  NOTE_E5, 150,
  NOTE_F5, 150,
  NOTE_D5, 300,
  NOTE_REST, 150,
  NOTE_E5, 150,
  NOTE_REST, 150,
  NOTE_F5, 150,
  NOTE_REST, 150,
  NOTE_G5, 1050,
  NOTE_REST, 300,
  NOTE_C5, 300,
  NOTE_D5, 150,
  NOTE_E5, 750,
  NOTE_C5, 300,
  NOTE_D5, 150,
  NOTE_E5, 450,
  NOTE_F5, 150,
  NOTE_G5, 150,
  NOTE_A5, 600,
  NOTE_C5, 300,
  NOTE_A5, 300,
  NOTE_G5, 300,
  NOTE_F5, 150,
  NOTE_E5, 750,
  TONES_END
};

const uint16_t *songs[MAX] = {
  little_star,
  kyou,
  (const uint16_t*)mirai
};

void selection_screen() {
  arduboy.clear();
  arduboy.setCursor(0, 0);
  const char **ii = titles;
  for (int i = 0; i < MAX; ++i, ++ii) {
    arduboy.print(i + 1);
    arduboy.print((char)0x20);
    if (i < MAX_IMPLEMENTED) {
      arduboy.println(*ii);
    } else {
      arduboy.println("Empty");
    }
  }
  arduboy.setCursor(6, sel << 3);
  arduboy.print('<');
}


void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.audio.on();
  selection_screen();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame()) {
    return;  
  }
  cur_state = arduboy.buttonsState();
  switch (state) {
  case STATE_SELECTION:
    if (!(old_state & UP_BUTTON) && (cur_state & UP_BUTTON)) {
      arduboy.setCursor(6, sel << 3);
      arduboy.print((char)0x20);
      --sel;
      sel &= 0x7;
      arduboy.setCursor(6, sel << 3);
      arduboy.print('<');
    }
    if (!(old_state & DOWN_BUTTON) && (cur_state & DOWN_BUTTON)) {
      arduboy.setCursor(6, sel << 3);
      arduboy.print((char)0x20);
      ++sel;
      sel &= 0x7;
      arduboy.setCursor(6, sel << 3);
      arduboy.print('<');
    }
    if (!(old_state & A_BUTTON) && (cur_state & A_BUTTON)) {
      if (sel < MAX_IMPLEMENTED) {
        arduboy.clear();
        state = STATE_PLAYING;
        arduboy.setCursor(0, 0);
        arduboy.print(titles[sel]);
        sound.tones(songs[sel]);
        f = 0;
        t = 0;
      }
    }
    break;
  case STATE_PLAYING:
    sprintf(buf, "%02d:%02d", t / 60, t % 60);
    arduboy.setCursor(0, 8);
    arduboy.print(buf);
    ++f;
    if (f == 60) {
      ++t;
      f = 0;
    }
    arduboy.setCursor(0, 8);
    
    if (!sound.playing()) {
      state = STATE_SELECTION;
      selection_screen();
    }
    if (!(old_state & B_BUTTON) && (cur_state & B_BUTTON)) {
      sound.noTone();
      state = STATE_SELECTION;
      selection_screen();
    }
    break;
  }
  old_state = cur_state;
  arduboy.display();
}
