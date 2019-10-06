import time
import rtmidi
import serial
import atexit
import serial.tools.list_ports
import sys

sounds = [ 57, 38, 41, 45, 42 ,36 ]

midiout = rtmidi.MidiOut()
available_ports = midiout.get_ports()

# here we're printing the ports to check that we see the one that loopMidi created.
# In the list we should see a port called "loopMIDI port".
print(available_ports)

# Attempt to open the port
if available_ports:
    midiout.open_port(1)
else:
    midiout.open_virtual_port("DRUMMER8002")

ports = list(serial.tools.list_ports.comports())
port = ""
if len(ports) > 1:
    print("Pick port:")
    for p in ports:
        print(p)
    port = ports[int(input("Which one? "))]
else:
    port = ports[0]

def main():
    try:
        ser = serial.Serial(port.device,9600)
        value = 0

        temp = ""
        while True:
            value = ser.read().decode()
            if value is not "\n":
                temp += value
            else:
                print("Playing pad# " + temp[0] + " at volume level " + temp[2:])
                #print(temp[0])
                #print(temp[2:])
                midi_stuff(int(temp[0]), abs(float(temp[2:])))
                #print(temp)
                temp = ""
            #time.sleep(0.001)
    except Exception as e:
        print("SAFELY QUIT")
        print(e)
        global midiout
        del midiout


def midi_stuff(dev,vol):

    note_on = [0x90, sounds[dev-1], (vol/3.48)*127]
    note_off = [0x80, sounds[dev-1], 0]
    midiout.send_message(note_on)
    #print("ON")
    #time.sleep(1)
    #print("OFF")
    # I tried running the script without having to invoke the sleep function but it doesn't work.
    # If someone could enlighten me as to why this is, I'd be more than grateful.
    midiout.send_message(note_off)

main()
