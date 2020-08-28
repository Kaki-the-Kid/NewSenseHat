/*****************************************************************//**
 * @file	SenseHat.h
 * @date	27. August 2020
 * @version	1.0
 * @author	krs - Karsten Reitan Sørensen
 * @details	SenseHat class - updated and extended
 * 
 * @brief	
  * This is based on the original from Philippe Simier, Christophe Grillo and Jon Dellaria
* 
 * Original code:
 * Philippe Simier: https://github.com/PhilippeSimier/SenseHat
 * 
 * 
 * 
 * 
 * -file SenseHat.h
 * -date 4 mars 2018
 * -version 1.2
 * -authors Philippe SIMIER Philippe CRUCHET Christophe GRILLO
 * -details Classe SenseHat : Gestion de la carte SenseHat
 * -version 1.3
 * -date 30 July 2019
 * -authors Jon Dellaria bug fixes, method translation to English and Temperature Measurement adjustments required for the Raspberry for a true temperature reading.
*********************************************************************/



#ifndef SENSEHAT_H
#define SENSEHAT_H


#define DEV_FB "/dev"
#define FB_DEV_NAME "fb"
#define DEV_INPUT_EVENT "/dev/input"
#define EVENT_DEV_NAME "event"

#define COULEUR uint16_t
#define COLOR_SENSEHAT uint16_t
#define PI 3.14159265

#define RED 	0xF800
#define BLUE    0x001F
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define BLACK   0x0000
#define ORANGE  0xFC00
#define CYAN    0x87FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <fcntl.h>
#include <sstream>
#include <math.h>
#include <iostream>
#include <iomanip>

//Linux bases libraries - currently working on windows machine
//todo - still needs to be tested on correct Raspberry Pi machine
//#include <dirent.h>
//#include <linux/fb.h>
//#include <sys/mman.h>
//#include <sys/ioctl.h>
//#include <unistd.h>
//#include <termios.h>
//#include <linux/input.h>

// Reference to the local url - working on a windows machine for the moment
// Part of this tast is to properly document RTIMULib for the student
#include "RTIMULib/usr/include/RTIMULib.h" //<RTIMULib.h>


struct fb_t {
	uint16_t pixel[8][8];
};


class SenseHat
{
private:
	int rotation = 0; // Default value for the direction of text on display, values: 0 90 180 270



public:
	SenseHat(); // Generel constructor for class
	~SenseHat(); // General deconstrucctor for class

	// For documentation and tutorials about operators, look at:
	// todo
	SenseHat& operator<<(SenseHat& (*)(SenseHat&));
	SenseHat& operator<<(const std::string&);
	SenseHat& operator<<(const int);
	SenseHat& operator<<(const double);
	SenseHat& operator<<(const char);
	SenseHat& operator<<(const char *);
	SenseHat& operator<<(const bool);


	//--------------------------------------------------------------------
	// Functions related to the LED Matrix on the Sense Hat
	//--------------------------------------------------------------------
	#pragma region led_related

	void InitialiserLeds();
	void InitializeLeds();
	void LightPixel(int ligne, int colonne, uint16_t couleur);
	uint16_t GetPixel(int ligne, int colonne);
	void ViewPattern(uint16_t motif[][8]);
	void RotatePattern(int rotation);
	void WipeScreen(uint16_t couleur = BLACK);

	COLOR_SENSEHAT ConvertRGB565(uint8_t red, uint8_t green, uint8_t blue);
	COLOR_SENSEHAT ConvertRGB565(uint8_t color[]);
	COLOR_SENSEHAT ConvertRGB565(std::string color);


	// @function			set_rotation
	// @description			If you're using the Pi upside down or sideways you can use 
	//						this function to correct the orientation of the image being shown.
	// @param	integer		r 
	//						0 90 180 270 //The angle to rotate the LED matrix though. 
	//						0 is with the Raspberry Pi HDMI port facing downwards.
	// @param	Boolean		redraw 
	//						True False	
	//						Whether or not to redraw what is already being displayed on the LED matrix.Defaults to True
	//	
	//	sense.set_rotation(180) OK
	//
	//	# alternatives: sense.rotation = 180
	void set_rotation(int newRotation) { rotation = newRotation; }


	// @function			flip_h
	// @description			Flips the image on the LED matrix horizontally.
	//
	// @param	boolean		redraw
	//						redraw	Boolean	True False	Whether or not to redraw what is already 
	//						being displayed on the LED matrix.Defaults to True

	//	@return				List
	//						A list containing 64 smaller lists of[R, G, B] pixels(red, green, blue) 
	//						representing the flipped image.
	//	sense.flip_h()
	void flip_h(bool redraw = true)
	{
		//todo!
	}


	// @function			flip_v
	// @description			Flips the image on the LED matrix vertically.
	//
	// @param Boolean		redraw
	//						Whether or not to redraw what is already being displayed on the LED 
	//						matrix when flipped. Defaults to True
	// @return				List
	//						A list containing 64 smaller lists of[R, G, B] pixels(red, green, blue) 
	//						representing the flipped image.
	// sense.flip_v()
	void flip_v(bool redraw = true)
	{
		//todo
	}


	// @function			set_pixels
	// @description			Updates the entire LED matrix based on a 64 length list of pixel values.
	// @param				pixel_list
	//						List [[R, G, B]* 64] A list containing 64 smaller lists of[R, G, B] 
	//						pixels(red, green, blue).Each R - G - B element must be an integer between 0 and 255.
	// @return				None
	// @usage
	//						X = [255, 0, 0]  # Red@
	//						O = [255, 255, 255]  # White
	//						question_mark = [
	//							O, O, O, X, X, O, O, O,
	//							O, O, X, O, O, X, O, O,
	//							O, O, O, O, O, X, O, O,
	//							O, O, O, O, X, O, O, O,
	//							O, O, O, X, O, O, O, O,
	//							O, O, O, X, O, O, O, O,
	//							O, O, O, O, O, O, O, O,
	//							O, O, O, X, O, O, O, O
	//						]
	void set_pixels()
	{
		//todo - this function already exist
	}




		//sense.set_pixels(question_mark)
		//		get_pixels
		//		Returned type	Explanation
		//		List	A list containing 64 smaller lists of[R, G, B] pixels(red, green, blue) representing the currently displayed image.
		//		from sense_hat import SenseHat

		//		sense = SenseHat()
		//		pixel_list = sense.get_pixels()
		//		Note: You will notice that the pixel values you pass into set_pixels sometimes change when you read them back with get_pixels.This is because we specify each pixel element as 8 bit numbers(0 to 255) but when they're passed into the Linux frame buffer for the LED matrix the numbers are bit shifted down to fit into RGB 565. 5 bits for red, 6 bits for green and 5 bits for blue. The loss of binary precision when performing this conversion (3 bits lost for red, 2 for green and 3 for blue) accounts for the discrepancies you see.

		//		The get_pixels function provides a correct representation of how the pixels end up in frame buffer memory after you've called set_pixels.

		//		set_pixel
		//		Sets an individual LED matrix pixel at the specified X - Y coordinate to the specified colour.

		//		Parameter	Type	Valid values	Explanation
		//		x	Integer	0 - 7	0 is on the left, 7 on the right.
		//		y	Integer	0 - 7	0 is at the top, 7 at the bottom.
		//		Colour can either be passed as an RGB tuple :
		//	pixel	Tuple or List(r, g, b)	Each element must be an integer between 0 and 255.
		//		Or three separate values for red, greenand blue :
		//	r	Integer	0 - 255	The Red element of the pixel.
		//		g	Integer	0 - 255	The Green element of the pixel.
		//		b	Integer	0 - 255	The Blue element of the pixel.
		//		Returned type	Explanation
		//		None
		//		from sense_hat import SenseHat

		//		sense = SenseHat()

		//		# examples using (x, y, r, g, b)
		//		sense.set_pixel(0, 0, 255, 0, 0)
		//		sense.set_pixel(0, 7, 0, 255, 0)
		//		sense.set_pixel(7, 0, 0, 0, 255)
		//		sense.set_pixel(7, 7, 255, 0, 255)

		//		red = (255, 0, 0)
		//		green = (0, 255, 0)
		//		blue = (0, 0, 255)

		//		# examples using (x, y, pixel)
		//		sense.set_pixel(0, 0, red)
		//		sense.set_pixel(0, 0, green)
		//		sense.set_pixel(0, 0, blue)
		//		get_pixel
		//		Parameter	Type	Valid values	Explanation
		//		x	Integer	0 - 7	0 is on the left, 7 on the right.
		//		y	Integer	0 - 7	0 is at the top, 7 at the bottom.
		//		Returned type	Explanation
		//		List	Returns a list of[R, G, B] representing the colour of an individual LED matrix pixel at the specified X - Y coordinate.
		//		from sense_hat import SenseHat

		//		sense = SenseHat()
		//		top_left_pixel = sense.get_pixel(0, 0)
		//		Note: Please read the note under get_pixels

		//		load_image
		//		Loads an image file, converts it to RGB format and displays it on the LED matrix.The image must be 8 x 8 pixels in size.

		//		Parameter	Type	Valid values	Explanation
		//		file_path	String	Any valid file path.The file system path to the image file to load.
		//		redraw	Boolean	True False	Whether or not to redraw the loaded image file on the LED matrix.Defaults to True
		//		from sense_hat import SenseHat

		//		sense = SenseHat()
		//		sense.load_image("space_invader.png")
		//		Returned type	Explanation
		//		List	A list containing 64 smaller lists of[R, G, B] pixels(red, green, blue) representing the loaded image after RGB conversion.
		//		from sense_hat import SenseHat

		//		sense = SenseHat()
		//		invader_pixels = sense.load_image("space_invader.png", redraw = False)
		//		clear
		//		Sets the entire LED matrix to a single colour, defaults to blank / off.

		//		Parameter	Type	Valid values	Explanation
		//		colour	Tuple or List(r, g, b)	A tuple or list containing the RGB(red, green, blue) values of the colour.Each element must be an integer between 0 and 255. Defaults to(0, 0, 0).
		//		Alternatively, the RGB values can be passed individually :
		//	r	Integer	0 - 255	The Red element of the colour.
		//		g	Integer	0 - 255	The Green element of the colour.
		//		b	Integer	0 - 255	The Blue element of the colour.
		//		from sense_hat import SenseHat
		//		from time import sleep

		//		sense = SenseHat()

		//		red = (255, 0, 0)

		//		sense.clear()  # no arguments defaults to off
		//		sleep(1)
		//		sense.clear(red)  # passing in an RGB tuple
		//		sleep(1)
		//		sense.clear(255, 255, 255)  # passing in r, g and b values of a colour
		//		show_message
		//		Scrolls a text message from right to left across the LED matrix and at the specified speed, in the specified colour and background colour.

		//		Parameter	Type	Valid values	Explanation
		//		text_string	String	Any text string.The message to scroll.
		//		scroll_speed	Float	Any floating point number.The speed at which the text should scroll.This value represents the time paused for between shifting the text to the left by one column of pixels.Defaults to 0.1
		//		text_colour	List[R, G, B]	A list containing the R - G - B(red, green, blue) colour of the text.Each R - G - B element must be an integer between 0 and 255. Defaults to[255, 255, 255] white.
		//		back_colour	List[R, G, B]	A list containing the R - G - B(red, green, blue) colour of the background.Each R - G - B element must be an integer between 0 and 255. Defaults to[0, 0, 0] black / off.
		//		Returned type	Explanation
		//		None
		//		from sense_hat import SenseHat

		//		sense = SenseHat()
		//		sense.show_message("One small step for Pi!", text_colour = [255, 0, 0])
		//		show_letter
		//		Displays a single text character on the LED matrix.

		//		Parameter	Type	Valid values	Explanation
		//		s	String	A text string of length 1.	The letter to show.
		//		text_colour	List[R, G, B]	A list containing the R - G - B(red, green, blue) colour of the letter.Each R - G - B element must be an integer between 0 and 255. Defaults to[255, 255, 255] white.
		//		back_colour	List[R, G, B]	A list containing the R - G - B(red, green, blue) colour of the background.Each R - G - B element must be an integer between 0 and 255. Defaults to[0, 0, 0] black / off.
		//		Returned type	Explanation
		//		None
		//		import time
		//		from sense_hat import SenseHat

		//		sense = SenseHat()

		//		for i in reversed(range(0, 10)) :
		//			sense.show_letter(str(i))
		//			time.sleep(1)
		//			low_light
		//			Toggles the LED matrix low light mode, useful if the Sense HAT is being used in a dark environment.

		//			import time
		//			from sense_hat import SenseHat

		//			sense = SenseHat()
		//			sense.clear(255, 255, 255)
		//			sense.low_light = True
		//			time.sleep(2)
		//			sense.low_light = False
		//			gamma
		//			For advanced users.Most users will just need the low_light Boolean property above.The Sense HAT python API uses 8 bit(0 to 255) colours for R, G, B.When these are written to the Linux frame buffer they're bit shifted into RGB 5 6 5. The driver then converts them to RGB 5 5 5 before it passes them over to the ATTiny88 AVR for writing to the LEDs.

		//			The gamma property allows you to specify a gamma lookup table for the final 5 bits of colour used.The lookup table is a list of 32 numbers that must be between 0 and 31. The value of the incoming 5 bit colour is used to index the lookup table and the value found at that position is then written to the LEDs.

		//			Type	Valid values	Explanation
		//			Tuple or List	Tuple or List of length 32 containing Integers between 0 and 31	Gamma lookup table for the final 5 bits of colour
		//			import time
		//			from sense_hat import SenseHat

		//			sense = SenseHat()
		//			sense.clear(255, 127, 0)

		//			print(sense.gamma)
		//			time.sleep(2)

		//			sense.gamma = reversed(sense.gamma)
		//			print(sense.gamma)
		//			time.sleep(2)

		//			sense.low_light = True
		//			print(sense.gamma)
		//			time.sleep(2)

		//			sense.low_light = False
		//			gamma_reset
		//			A function to reset the gamma lookup table to default, ideal if you've been messing with it and want to get it back to a default state.

		//			Returned type	Explanation
		//			None
		//			import time
		//			from sense_hat import SenseHat

		//			sense = SenseHat()
		//			sense.clear(255, 127, 0)
		//			time.sleep(2)
		//			sense.gamma = [0] * 32  # Will turn the LED matrix off
		//			time.sleep(2)
		//			sense.gamma_reset()

					/**  */

	#pragma endregion //led_related

	char ScannerJoystick();
	char ScanJoystick();

	float ObtenirTemperature();
		float GetTemperature();

		float correctTemperature(float senseHatTemp, float cpuTemp);
		float getRawTemperature();
		float getCpuTemperature();

	float ObtenirPression();
		float GetPressure();

	float ObtenirHumidite();
		float GetHumidity();

	void  ObtenirOrientation(float &pitch, float &roll, float & yaw);
		void  GetOrientation(float &pitch, float &roll, float & yaw);

	void  ObtenirAcceleration(float &x, float &y, float &z);
		void  GetAcceleration(float &x, float &y, float &z);

	void  ObtenirMagnetisme(float &x, float &y, float &z);
		void  GetMagnetism(float &x, float &y, float &z);

	void  ObtenirMagnetismeSpherique(float &ro, float &teta, float &delta);
		void  GetSphericalMagnetism(float &ro, float &teta, float &delta);

	void  Version();
	void  Flush();

	void  FixerCouleur(uint16_t);
		void  SetColor(uint16_t);

	void  FixerRotation(uint16_t);
		void  SetRotation(uint16_t);

private:
	void  InitialiserJoystik();
		void  InitializeJoystick();

	void  InitialiserPression();
		void  InitializePressure();

	void  InitialiserHumidite();
		void  InitializeHumidity();

	void  InitialiserOrientation();
		void  InitializeOrientation();

	void  InitialiserAcceleration();
		void  InitializeAcceleration();

	void ConvertirCaractereEnMotif(char c, uint16_t image[8][8], uint16_t couleurTexte, uint16_t couleurFond);
		void ConvertCharacterToPattern(char c, uint16_t image[8][8], uint16_t couleurTexte, uint16_t couleurFond);

	bool ColonneVide(int numColonne, uint16_t image[8][8], uint16_t couleurFond);
		bool EmptyColumn(int numColonne, uint16_t image[8][8], uint16_t couleurFond);

	void TassementDeLimage(int numColonne, uint16_t image[][8][8], int taille);
		void ImageContainment(int numColonne, uint16_t image[][8][8], int taille);

	struct fb_t *fb;
	int joystick;
	RTIMUSettings *settings;
	RTIMU *imu;
	RTPressure *pressure;
	RTHumidity *humidite;
	std::string buffer;
	uint16_t couleur;
	int rotation;
};

// surcharge des manipulators
SenseHat& endl(SenseHat& os);
SenseHat& flush(SenseHat& os);

// surcharge du manipulateur setcouleur
struct _SetCouleur { int val; };
_SetCouleur setcouleur(int n);
SenseHat&  operator<<(SenseHat& os, _SetCouleur couleur);

// surcharge du manipulateur setrotation
struct _SetRotation { int val; };
_SetRotation setrotation(int n);
SenseHat&  operator<<(SenseHat& os, _SetRotation rotation);
#endif // SENSEHAT_H
