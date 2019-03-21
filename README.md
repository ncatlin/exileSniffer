# exileSniffer v1.0.1

-------------

Important Note! 
This is a proof of concept for a game reversing blog post: it worked with POE as of April 2018, which obviously isn't now. 
Every expansion (and many of the little updates) makes changes to the game stream which breaks decryption and the changes have to be reverse engineered and added to the sniffer code. 
I don't play the game so the motivation to keep it updated isn't staggering.

If you are more keen on doing this than I am then you are welcome to fork it or read the code to figure out how to make your own tool. 

--------------

A protocol decryption and dissection tool for the game 'Path of Exile'

It looks something like this:

<img src="https://i.imgur.com/mAIEXzr.png" width="400">

As well as decrypting the login and game streams, it breaks it up into its constituent packets and outputs them to disk and the UI dissection pane. Further analysis of each packet is provided (where available - this is an ongoing reverse engineering task) and can be browsed in the UI. It can also be read from a named pipe for access with external tools.

For example, this Python script will print changes to your characters health

```
import json
import codecs

def connectToPipe():
    pipename = "\\\\.\\pipe\\ExilePipe"
    pipe = codecs.open(pipename, 'rb', encoding='utf-16-le')
    return pipe

if __name__ == "__main__":

    currentPlayerID = 0
    
    pipe = connectToPipe()
    while True:
        ln = pipe.readline()
        if len(ln) == 0: continue
        js = json.loads(ln)

        if js['MsgType'] == 'SRV_NOTIFY_PLAYERID':
            currentPlayerID = js['Payload']['ID1']
            continue

        if js['MsgType'] == 'SRV_MOBILE_UPDATE_HMS':
            if js['Payload']['Stat'] == 0: #life
                print(js['Payload']['NewValue'])
            continue
```

For the long explanation of what it is and how it works read [this](https://tbinarii.blogspot.co.uk/2018/05/reverse-engineering-path-of-exile.html)

Latest Changelog
----------

Version 1.0.1
		
	Memory changes: 
		Packets now use less memory.
		Filtered messages were consuming far too much memory so they are now discarded.
		Previously filtered messages will not return when the filters are cleared. Refer to the logfiles to recover them if needed.
		I'll implement a hex->packet reconstruction utility soon.
		
	Handle more packets
		0x3b - CLI_USE_ITEM_ON_OBJ
		0x81 - SRV_CHANGE_LIGHTING
		0x82 - CLI_TRANSFER_ITEM
		0xdb - SRV_NOTIFY_AFK
		0xf6 - SRV_UNK_0xf6

	Improve existing packets
		0x75 - SRV_MOVE_OBJECT

	Minor display/naming improvements:
		0x70 - SRV_GRANTED_XP
		0xA3 - CLI_UNK_A3
		0xF3 - CLI_UNK_F3


How it works
----------

exileSniffer doesn't modify the Path of Exile binary or its memory. There are no code caves or hardcoded offsets to pointer chains or any of that awful stuff - just some heureustics to read the session key from process memory during login. It then closes the process handle and never interacts with it again (or until the player logs out). All the other information is obtained by network sniffing.

Using
----------

[Download here](https://github.com/ncatlin/exileSniffer/releases/download/1.0.1/exileSniffer.7z)


(SHA256 = 84821EA23D0B117C761FB79BADE5136D63ED9A0F3FC347397C4D2B3E7684DC23)

Be running Windows. 
Unzip the archive with 7zip.  

Make sure [WinPcap](https://www.winpcap.org/install/default.htm) is installed. If you can sniff with wireshark, you should be able to sniff with this.

*If you get a message about wpcap.dll not being found - you need to install winpcap*.

Run exilesniffer.exe. Login to Eath of Exile.

exileSniffer must be running before you log in to your account.

Once you have logged in, wait for the decryption to sync up.

<img src="https://i.imgur.com/5rLdaKD.png" width="400">

Once that is done the packet list will be displayed

<img src="https://i.imgur.com/arZijYh.png" width="400">

You can now press play and decrypt the game stream.

Notes
----------

Much of the indepth display of packet contents relies on PyPoE extracted game data. This data is provided as ggpk_exports.json, but you can generate your own with the provided gen_ggpk_exports.py if you have PyPoE setup for your Python installation.

I've occasionally encountered a bug where the transition from login stream to game stream doesn't happen, but haven't narrowed down the cause yet.

Contributing
----------

Many packet types are not analysed yet. If you notice a new packet (there are many!) you are welcome to submit pull requests, even updates to *messageTypes.json* are useful.
