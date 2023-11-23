For Arduino Nano
	Code was written with IDE 1.8.12 and some have also been checked with 1.8.13,
	Clones:
		You will likely need to download and install the CH340 or CH341 device drivers. Just search for
			CH340 device driver in your browser.
		If the code will not upload, most clones use the old bootloader. Use Tools --> Bootloader to select 
			the old bootloader.
			NOte: This setting does not appear to be saved between reloads.
		

For ESP32

	For a pretty good description of installing the patch, see:
		https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
		
	To install the software patch for the ESP32, put this:

		https://dl.espressif.com/dl/package_esp32_index.json 

	into the “Additional Board Manager URLs” field of the File --> Preferences dialog box. 
	Then, click the “OK”.
	
	Now select Boards Manager from Tools --> Boards --> Boards Manager and tye:
	
		ESP32
		
	into the right-top textbox and select ESP32 and click Install
	
	
For STM32

	First, read this:
	
		https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation

	Download Roger Clarks patch from:
	
		https://github.com/rogerclarkmelbourne/Arduino_STM32
		
	and save the ZIP file in your Arduino hardware subdirectory (e.g., C:\Arduino1.8.13\hardware).
	
	Extract the files in the ZIP file. (If you use WIndows Explore, double-click the ZIP file to 
	extract. Extract into the hardware subdirectory (e.g., C:\Arduino1.8.13\hardware).
	
	When extraction is finished, you will have a directory named Arduino_STM32_master. You MUST
	rename this subdirectory from Arduino_STM32_master to Arduino_STM32. Now if you look in the
	hardware subdirectory, you will see:
	
			hardware\Arduinjo_STM32\
															drivers
															STM32F1
															STm32f4
															tools
															// more files...
															
	You will also see the STM32 boards listed in the Tools --> Boards list after you reload the Ardunio IDE.
	A post by Roger said that it may be necessary to install the SAMD library for the Arduino Due for some
	clones. It won't hurt anything to install it.
	
	For the STM32Duino:
	
	https://github.com/stm32duino/BoardManagerFiles/raw/master/STM32/package_stm_index.json
	
Teensy

	This is a really easy patch...Paul has done a wonderful job of making his install easy. Download the 
	Teensyduino patch from:
	
		https://www.pjrc.com/teensy/td_download.html
		
	and just save it somewhere cconvenient. Run the program and it will ask you the name of the Arduino
	folder (i.e., directory) where you stored the Arduino IDE (e.g., C:\Arduino1.8.13). Once that's done, 
	just click the Next button and opt for all of the files to be installed. It will then proceed to 
	install the patch. When you are done, you should see the teensy subdirectory 
	(e.g., C:\Arduino1.8.13\hardware\teensy).