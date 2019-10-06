/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

//==============================================================================
HudrumTrigAudioProcessorEditor::HudrumTrigAudioProcessorEditor (HudrumTrigAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

HudrumTrigAudioProcessorEditor::~HudrumTrigAudioProcessorEditor()
{
}

void thathappend() {
    
}

void enumerate_ports()
{
    StringPairArray portlist = SerialPort::getSerialPortPaths();
    if(portlist.size())
    {
        //open the first port on the system
        SerialPort * pSP = new SerialPort(portlist.getAllValues()[0], SerialPortConfig(9600, 8, SerialPortConfig::SERIALPORT_PARITY_NONE, SerialPortConfig::STOPBITS_1, SerialPortConfig::FLOWCONTROL_NONE));
        if(pSP->exists())
        {
            //create streams for reading/writing
            SerialPortOutputStream * pOutputStream = new SerialPortOutputStream(pSP);
            SerialPortInputStream * pInputStream = new SerialPortInputStream(pSP);

            pOutputStream->write("hello world via serial", 22); //write some bytes

            //read chars one at a time:
            char c;
            while(!pInputStream->isExhausted())
                pInputStream->read(&c, 1);

            //or, read line by line:
            String s;
            while(pInputStream->canReadLine())
                s = pInputStream->readNextLine();

            //or ask to be notified when a new line is available:
            //pInputStream->addChangeListener(this); //we must be a ChangeListener to receive notifications
            pInputStream->setNotify(SerialPortInputStream::NOTIFY_ON_CHAR, '\n');

            //or ask to be notified whenever any character is received
            //NOTE - use with care at high baud rates!!!!
            pInputStream->setNotify(SerialPortInputStream::NOTIFY_ALWAYS);

            //please see class definitions for other features/functions etc
        }
    }
}

//==============================================================================
void HudrumTrigAudioProcessorEditor::paint (Graphics& g)
{
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void HudrumTrigAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
