/*
	saveManager.hpp

	Utility that handles the save file stream. It uses the fat.h header to access
	the SD card/USB device. After the device initialization it is possible to use
	fstream as well as other libraries for file input/output.
*/

#include <fat.h>
#include <fstream>

class SaveManager {
public:
	// Class constructor
	SaveManager() {
		// This function initializes the preferred device for file input/output.
		// It checks first for an SD card, then for a USB device.
		fatInitDefault();
	}
	// Load the save from a file
	void Load() {
		std::ifstream save;
     	save.open("/apps/DoodleWiiJump/game.sav", std::ifstream::in);
     	// If the file exists, load the data from it
     	if(!save.fail())
     	{
     		save >> aspectRatio;
     		save >> highScore;
     	}
     	// Else, load the default values
     	else
     	{
     		aspectRatio = 0.75;
     		highScore = 0;
     	}

     	save.close();
	}
	// Save data to file
	void Save(float _aspectRatio, int _highScore) {
		std::ofstream save;
		save.open("/apps/DoodleWiiJump/game.sav");

		save << _aspectRatio << std::endl << _highScore;

		save.close();
	}
	// Get() methods for the aspect ratio and the high score
	float getAspectRatio() { return aspectRatio; }
	int getHighScore() { return highScore; }
private:
	float aspectRatio = 0;
	int highScore = 0;
};