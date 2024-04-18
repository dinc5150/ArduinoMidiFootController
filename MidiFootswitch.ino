#include <Encoder.h>
#include <Control_Surface.h>

USBMIDI_Interface midi;

// Four banks to change the channel of the potentiometer
Bank<3> bank(4);
 
// Selector to change banks
IncrementSelectorLEDs<3> bankSelector {
  bank,
  Button{
    1
  },         // button pins
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




class ToggleButton{

  public:
    
    ToggleButton(int pin, int midiCC, MIDIChannelCable channel){
      this->pin = pin;
      this->midiCC = midiCC;
      this->channel = channel;
      this->button = Button{pin}; 
      this->stompBtnDown = 0;
    }
    Button button;
 
  void ToggleButton::update(){

    this->button.update();

    if(button.getState() == AH::Button::State::Pressed){
        
        if(this->stompBtnDown == 0){
          //start counting
          this->stompBtnDown = millis();
        }
    
    }else if(this->stompBtnDown != 0 && this->button.getState() == AH::Button::State::Released){
      //Just released button
      if(millis() - this->stompBtnDown < 1000){
        //Normal Press


        this->stompBtnDown=0;

        this->isOn = !this->isOn;
        Control_Surface.sendControlChange({this->midiCC, this->channel}, (this->isOn)? 127 : 0);

        Serial.print("Toggled Btn");
        Serial.println(this->pin);
        Serial.print(" ");
        Serial.println(this->isOn);
        //Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_4, CHANNEL_2}, 0x40);
    


        // Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_4, CHANNEL_2}, 0x40);
      }else{
        //Long Press
        this->stompBtnDown=0;
        Serial.println(millis());
        Serial.println(this->stompBtnDown);
        //Todo: Lets Figure out what to do here
        //Control_Surface.sendControlChange({0x27, CHANNEL_1}, 127);
      
      }
    }
  };


  private:
    int pin;
    int midiCC;
    MIDIChannelCable channel;
    bool isOn = false;
    unsigned long stompBtnDown;
};




Bankable::CCAbsoluteEncoder<3>  enc1[] {

  //Preamp
   {
      {bank, BankType::CHANGE_ADDRESS},
      {16, 9},       // pins
      {MIDI_CC::Sound_Controller_6, CHANNEL_1},
    //MCU::V_POT_1, // MIDI address (CC number + optional channel)
      5,            // optional multiplier if the control isn't fast enough
    },

//Reverb Knob
   {
     {bank, BankType::CHANGE_ADDRESS},
  {18, 10},       // pins
  {MIDI_CC::Sound_Controller_7, CHANNEL_1},
 //MCU::V_POT_1, // MIDI address (CC number + optional channel)
  5,            // optional multiplier if the control isn't fast enough
},


//Compressor
// {
//   {bank, BankType::CHANGE_CHANNEL},
//   {19, 14},       // pins
//   {MIDI_CC::Sound_Controller_8, CHANNEL_1},
//  //MCU::V_POT_1, // MIDI address (CC number + optional channel)
//   5,            // optional multiplier if the control isn't fast enough
// },

//Volume Knob
  {
    {bank, BankType::CHANGE_ADDRESS},
    {20, 15},       // pins
    {MIDI_CC::Channel_Volume, CHANNEL_1},
  //MCU::V_POT_1, // MIDI address (CC number + optional channel)
    5,            // optional multiplier if the control isn't fast enough
  }

};



// Bankable::CCAbsoluteEncoder<3> enc1[] {

//   //Preamp
//    {
//       {bank, BankType::CHANGE_CHANNEL},
//       {16, 9},       // pins
//       {MIDI_CC::Sound_Controller_6, CHANNEL_1},
//     //MCU::V_POT_1, // MIDI address (CC number + optional channel)
//       5,            // optional multiplier if the control isn't fast enough
//     },

// //Reverb Knob
//    {
//      {bank, BankType::CHANGE_CHANNEL},
//   {18, 10},       // pins
//   {MIDI_CC::Sound_Controller_7, CHANNEL_1},
//  //MCU::V_POT_1, // MIDI address (CC number + optional channel)
//   5,            // optional multiplier if the control isn't fast enough
// },


// //Compressor
// {
//   {bank, BankType::CHANGE_CHANNEL},
//   {19, 14},       // pins
//   {MIDI_CC::Sound_Controller_8, CHANNEL_1},
//  //MCU::V_POT_1, // MIDI address (CC number + optional channel)
//   5,            // optional multiplier if the control isn't fast enough
// },

// //Volume Knob
//   {
//     {bank, BankType::CHANGE_CHANNEL},
//     {20, 15},       // pins
//     {MIDI_CC::Channel_Volume, CHANNEL_1},
//   //MCU::V_POT_1, // MIDI address (CC number + optional channel)
//     5,            // optional multiplier if the control isn't fast enough
//   }

// };





// ROTARY ENCODER Buttons

//NOTE: Button 1 changes banks
// CCButton encBtn1 {
//  1,// Push button on pin 5:
//   {MIDI_CC::Effects_1, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
// };

// CCButton encBtn2 {
//   2,// Push button on pin 5:
//   {MIDI_CC::General_Purpose_Controller_5, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
// };

//  CCButton encBtn3 {
//   3,// Push button on pin 5:
//    {MIDI_CC::General_Purpose_Controller_6, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
//  };
ToggleButton encBtn2 = ToggleButton( 2,  MIDI_CC::General_Purpose_Controller_5,  CHANNEL_1 );
ToggleButton encBtn3 = ToggleButton( 3,  MIDI_CC::General_Purpose_Controller_6,  CHANNEL_1 );
ToggleButton encBtn4 = ToggleButton( 4,  MIDI_CC::General_Purpose_Controller_7,  CHANNEL_1 );

// CCButton encBtn4 {
//  4,// Push button on pin 5:
//   {MIDI_CC::General_Purpose_Controller_7, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
// };
// Button encBtn4 {
//   4 //Pin
// };


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



Bankable::PCButton btnPC1 {
  {bank, BankType::CHANGE_ADDRESS},
 5,// Push button on pin 5:
  {MIDI_PC::Acoustic_Grand_Piano, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};

Bankable::PCButton btnPC2 {
    {bank, BankType::CHANGE_ADDRESS},
 6,// Push button on pin 5:
  {MIDI_PC::Bright_Acoustic_Piano, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};

Bankable::PCButton btnPC3 {
    {bank, BankType::CHANGE_ADDRESS},
 7,// Push button on pin 5:
  {MIDI_PC::Electric_Grand_Piano, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};

Bankable::PCButton btnPC4 {
    {bank, BankType::CHANGE_ADDRESS},
 8,// Push button on pin 5:
  {MIDI_PC::HonkyTonk_Piano, CHANNEL_1}, // General Purpose Controller #1 1on MIDI channel 1:
};


void setup() {
  Serial.begin(115200);
  // Wait until serial port is opened
  //while (!Serial) { delay(1); }



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
  RelativeCCSender::setMode(relativeCCmode::BINARY_OFFSET);
Control_Surface.begin();

  btn1.disable();
  btn2.disable();
  btn3.disable();
  btn4.disable();


}



long stompBtnDown = 0;

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



  //Serial.println(encBtn4.getButtonState());



  //midi.update();
  Control_Surface.loop();

  encBtn2.update();
  encBtn3.update();
  encBtn4.update();

// Button::State oldState = encBtn4.getState();
// Button::State newState = encBtn4.update();
//   if(oldState != newState){
// Serial.println(oldState);
// Serial.println(newState);

//   }


// if(encBtn4.getState() == AH::Button::State::Pressed){

//   if(stompBtnDown == 0){
//     Serial.println(encBtn4.getState());
// Serial.println(encBtn4.update());
//     //start counting
//     stompBtnDown = millis();
//   }
// }else if(stompBtnDown != 0 && encBtn4.getState() == AH::Button::State::Released){
//   //Just released button
//   if(millis() - stompBtnDown < 1000){
//     stompBtnDown=0;
//     //Normal Press
//      Control_Surface.sendControlChange({MIDI_CC::General_Purpose_Controller_4, CHANNEL_2}, 0x40);
//   }else{
//     //Long Press
//     stompBtnDown=0;
//     Control_Surface.sendControlChange({0x27, CHANNEL_1}, 127);
//   }
// }


}

