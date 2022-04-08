#include <Encoder.h>
#include <Control_Surface.h>

USBMIDI_Interface midi;

// Four banks to change the channel of the potentiometer
Bank<3> bank(1);
 
// Selector to change banks
IncrementSelectorLEDs<3> bankSelector {
  bank,
  {1},         // button pins
  {21, 0, 22}, // LED pins -- 22 is not a pin. Not sure if this is going to cause an issue
};

 // MIDIAddress note = {MIDI_Notes::C(4), CHANNEL_6};
//const MIDIAddress address {MIDI_Notes::C, CHANNEL_1};
//const MIDIAddress address {4, CHANNEL_1};
//const MIDIAddress volumeChannel {MIDI_CC::Channel_Volume, CHANNEL_1};
//const uint8_t velocity = 0x7F;


/*
CCButton button {
 5,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_1, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};*/


/* EFFECTS DESCRIPTIONS

Notes List : https://anotherproducer.com/online-tools-for-musicians/midi-cc-list/

*/





Bankable::CCAbsoluteEncoder<3> enc1[] {

  //Preamp
   {
      {bank, BankType::CHANGE_CHANNEL},
      {16, 9},       // pins
      {MIDI_CC::Sound_Controller_6, CHANNEL_1},
    //MCU::V_POT_1, // MIDI address (CC number + optional channel)
      5,            // optional multiplier if the control isn't fast enough
    },

//Reverb Knob
   {
     {bank, BankType::CHANGE_CHANNEL},
  {18, 10},       // pins
  {MIDI_CC::Sound_Controller_7, CHANNEL_1},
 //MCU::V_POT_1, // MIDI address (CC number + optional channel)
  5,            // optional multiplier if the control isn't fast enough
},


//Compressor
{
  {bank, BankType::CHANGE_CHANNEL},
  {19, 14},       // pins
  {MIDI_CC::Sound_Controller_8, CHANNEL_1},
 //MCU::V_POT_1, // MIDI address (CC number + optional channel)
  5,            // optional multiplier if the control isn't fast enough
},

//Volume Knob
  {
    {bank, BankType::CHANGE_CHANNEL},
    {20, 15},       // pins
    {MIDI_CC::Channel_Volume, CHANNEL_1},
  //MCU::V_POT_1, // MIDI address (CC number + optional channel)
    5,            // optional multiplier if the control isn't fast enough
  }

};


// CCButton encBtn1 {
//  1,// Push button on pin 5:
//   {MIDI_CC::Effects_1, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
// };

CCButton encBtn2 {
 2,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_5, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};

//  CCButton encBtn3 {
//   3,// Push button on pin 5:
//    {MIDI_CC::General_Purpose_Controller_6, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
//  };

CCButton encBtn4 {
 4,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_7, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};


CCButton btn1 {
 5,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_1, CHANNEL_2}, // General Purpose Controller #1 1on MIDI channel 1:
};

CCButton btn2 {
 6,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_2, CHANNEL_2}, // General Purpose Controller #1 1on MIDI channel 1:
};

CCButton btn3 {
 7,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_3, CHANNEL_2}, // General Purpose Controller #1 1on MIDI channel 1:
};

CCButton btn4 {
 8,// Push button on pin 5:
  {MIDI_CC::General_Purpose_Controller_4, CHANNEL_2}, // General Purpose Controller #1 1on MIDI channel 1:
};


void setup() {
  Serial.begin(115200);
  // Wait until serial port is opened
  //while (!Serial) { delay(1); }

 // Serial.println("Adafruit DS3502 Test");
  // put your setup code here, to run once:

//midi.begin();


 // Select the correct relative MIDI CC mode.
  // Options:
  //   - TWOS_COMPLEMENT (default)
  //   - BINARY_OFFSET
  //   - SIGN_MAGNITUDE
  //   - NEXT_ADDRESS
  // Aliases:
  //   - REAPER_RELATIVE_1
  //   - REAPER_RELATIVE_2
  //   - REAPER_RELATIVE_3
  //   - TRACKTION_RELATIVE
  //   - MACKIE_CONTROL_RELATIVE
  //   - KORG_KONTROL_INC_DEC_1
  RelativeCCSender::setMode(relativeCCmode::TWOS_COMPLEMENT);
Control_Surface.begin();
}





void loop() {
  //Serial.println("loop");
  //delay(1000);


//Manual Send Controls
/*
  midi.sendCC(address,0);
  delay(500);
 // midi.sendNoteOff(address, velocity);
 midi.sendCC(address,velocity);
  delay(500);
 */




  //midi.update();
  Control_Surface.loop();
}