/*
	main.cpp

	Main file for the project, includes the main menu, the game loop
	and the entry point for the game
*/

#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <vector>
#include <time.h>
#include <string>

// Include the textures
#include "bck_png.h"
#include "likRight_png.h"
#include "likLeft_png.h"
#include "platform_png.h"
#include "hole_png.h"
#include "title_png.h"
#include "play_png.h"
#include "playagain_png.h"
#include "options_png.h"
#include "exit_png.h"
#include "menu_tear_png.h"

#include "font_ttf.h"

// Custom headers
#include "entity.hpp"
#include "platform.hpp"
#include "player.hpp"
#include "button.hpp"
#include "dataTypes.hpp"
#include "saveManager.hpp"

// Define some colors
#define WHITE 0xFFFFFFFF
#define BLACK 0x000000FF
#define RED 0xFF0000FF

// Other defines
#define ASPECT_RATIO_16_9 0.75
#define ASPECT_RATIO_4_3 1

// 0.75 for 16/9, 1 for 4/3
float aspectRatioX = ASPECT_RATIO_16_9;

void ResetPlatforms(std::vector<Platform>& _platforms, GRRLIB_texImg *_texture);
void SwitchAspectRatio(float ratio);
void HighlightButton(std::vector<Button>& _buttons, int _index);
void SelectButton(std::vector<Button>& _buttons, int _index);
void Save();
void Load();

int main(void) {	
	// Initialise random seed
	srand(time(NULL));

    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();

    // Load the textures
    GRRLIB_texImg *backgroundSprite = GRRLIB_LoadTexture(bck_png);
    GRRLIB_texImg *playerSpriteRight = GRRLIB_LoadTexture(likRight_png);
    GRRLIB_texImg *playerSpriteLeft = GRRLIB_LoadTexture(likLeft_png);
    GRRLIB_texImg *platformSprite = GRRLIB_LoadTexture(platform_png);
    GRRLIB_texImg *titleSprite = GRRLIB_LoadTexture(title_png);
    GRRLIB_texImg *playSprite = GRRLIB_LoadTexture(play_png);
    GRRLIB_texImg *playAgainSprite = GRRLIB_LoadTexture(playagain_png);
    GRRLIB_texImg *optionsSprite = GRRLIB_LoadTexture(options_png);
    GRRLIB_texImg *exitSprite = GRRLIB_LoadTexture(exit_png);
    GRRLIB_texImg *menuTearSprite = GRRLIB_LoadTexture(menu_tear_png);

    // Save manager
    SaveManager saveManager = SaveManager();
    saveManager.Load();
    SwitchAspectRatio(saveManager.getAspectRatio());

    // Load the font
    GRRLIB_ttfFont *font = GRRLIB_LoadTTF(font_ttf, font_ttf_size);

    // Player object, shared between the title screen (for the animation) and the actual game
    Player player = Player(100, 300, playerSpriteRight, playerSpriteLeft);

    // Platforms vector, share between the title screen (the platform under the player) and the actual game
    std::vector<Platform> platforms;

    // The platform under the player
    platforms.push_back(Platform(100, 360, platformSprite));

    // Main menu

    // High score
    int highScore = saveManager.getHighScore();

    // Alpha component of the rectangle used for fading screens
    int alphaFadeRectangle = 0;

    // Are the settings opened?
    bool isSettingsOpened = false;
    // Which button has been highlighted?
    unsigned int buttonHigh = 0;
    unsigned int settingsHigh = 0;
    // Buttons array (main menu); buttons have to be defined manually
    std::vector<Button> menuButtons;
    menuButtons.push_back(Button(200, 150, playSprite));
    menuButtons.push_back(Button(225, 225, optionsSprite));
    menuButtons.push_back(Button(250, 300, exitSprite));

    // Buttons array (settings)
    std::vector<Button> settings;
    settings.push_back(Button(175, 250, font, "16:9"));
    settings.push_back(Button(225, 250, font, "4:3"));
    settings.push_back(Button(275, 250, font, "Reset high score"));

    // Highlight the first button
    menuButtons[buttonHigh].SetHighlighted(true);
    settings[settingsHigh].SetHighlighted(true);

    // Set selected state on button
    if (aspectRatioX == ASPECT_RATIO_16_9)
    	settings[0].SetSelected(true);
    else
    	settings[1].SetSelected(true);

    // Background (shared) and title
    Entity background = Entity(0, 0, backgroundSprite);
    Entity menuTear = Entity(440, 0, menuTearSprite);
    Entity title = Entity(100, 65, titleSprite);

    bool hasGameStarted = false;

    // Main menu loop
    while(1) {
    	// Scan for wiimotes
    	WPAD_ScanPads();

    	// Main menu
    	if (!hasGameStarted)
    	{
    		// Home button: close
    		if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  {
    			GRRLIB_Exit();
    			exit(0);
    		}
    		// Scroll up
	    	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_RIGHT) && !isSettingsOpened) {
	    		if (!buttonHigh == 0)
	    			buttonHigh--;
	    		HighlightButton(menuButtons, buttonHigh);
	    	}
	    	// Scroll down
	    	if ((WPAD_ButtonsDown(0) & WPAD_BUTTON_LEFT) && !isSettingsOpened) {
	    		if (buttonHigh + 1 < menuButtons.size())
	    			buttonHigh++;
	    		HighlightButton(menuButtons, buttonHigh);
	    	}
	    	// Settings: scroll left
	    	if (WPAD_ButtonsDown(0) & WPAD_BUTTON_UP && isSettingsOpened) {
	    		if (!settingsHigh == 0)
	    			settingsHigh--;
	    		HighlightButton(settings, settingsHigh);
	    	}
	    	// Settings: scroll right
	    	if (WPAD_ButtonsDown(0) & WPAD_BUTTON_DOWN && isSettingsOpened) {
	    		if (settingsHigh + 1 < settings.size())
	    			settingsHigh++;
	    		HighlightButton(settings, settingsHigh);
	    	}
	    	// Go back
	    	if (WPAD_ButtonsDown(0) & WPAD_BUTTON_1) {
	    		isSettingsOpened = false;
	    	}
	    	// Confirm
	    	if (WPAD_ButtonsDown(0) & WPAD_BUTTON_2) {
	    		if (!isSettingsOpened)
	    		{
	    			// Main menu
	    			switch(buttonHigh)
		    		{
		    			// Play
		    			case 0:
		    				hasGameStarted = true;
		    				break;
		    			// Open settings
		    			case 1:
		    				isSettingsOpened = true;
		    				break;
		    			// Quit game
		    			case 2:
		    				GRRLIB_Exit();
		    				exit(0);
		    		}
	    		}
	    		else
	    		{
	    			// Settings
	    			switch(settingsHigh)
	    			{
	    				// Set aspect ratio to 16:9
	    				case 0:
	    					SwitchAspectRatio(ASPECT_RATIO_16_9);
	    					SelectButton(settings, 0);
	    					saveManager.Save(ASPECT_RATIO_16_9, highScore);
	    					break;
	    				// Set aspect ratio to 4:3
	    				case 1:
	    					SwitchAspectRatio(ASPECT_RATIO_4_3);
	    					SelectButton(settings, 1);
	    					saveManager.Save(ASPECT_RATIO_4_3, highScore);
	    					break;
	    				// Reset save file
	    				case 2:
	    					saveManager.Save(aspectRatioX, 0);
	    					highScore = 0;
	    					break;
	    			}
	    		}
	    	}
    	}

    	// Fade animation
    	if (alphaFadeRectangle > 255)
        	break;
        if (hasGameStarted)
        	alphaFadeRectangle += 16;

        // Render
    	GRRLIB_FillScreen(WHITE);
        background.Render();
        for (unsigned int i = 0; i < platforms.size(); i++)
        {
        	platforms[i].Render();
        }

        player.Update();
       	player.CheckCollisionWithPlatform(platforms);
        player.Render();

        title.Render();
        GRRLIB_PrintfTTF(20, 450, font, "Made by Michele Lorusso, V1.0", 24, BLACK);

        menuTear.Render();

        GRRLIB_PrintfTTF(560 - GRRLIB_WidthTTF(font, "Controls", 36) / 2, 100, font, "Controls", 36, WHITE);
        GRRLIB_PrintfTTF(560 - GRRLIB_WidthTTF(font, "DPad - Select/Move", 20) / 2, 175, font, "DPad - Select/Move", 20, WHITE);
        GRRLIB_PrintfTTF(560 - GRRLIB_WidthTTF(font, "1 - Back", 20) / 2, 225, font, "1 - Back", 20, WHITE);
        GRRLIB_PrintfTTF(560 - GRRLIB_WidthTTF(font, "2 - Confirm", 20) / 2, 275, font, "2 - Confirm", 20, WHITE);
        GRRLIB_PrintfTTF(560 - GRRLIB_WidthTTF(font, "HOME - Exit at any time", 18) / 2, 325, font, "HOME - Exit at any time", 18, WHITE);

        for (unsigned int i = 0; i < menuButtons.size(); i++)
        {
        	// We need a special check for the settings button
        	if (i != 1)
        		menuButtons[i].Render();
        }
        if (!isSettingsOpened)
        	menuButtons[1].Render();
        else
        {
        	GRRLIB_PrintfTTF(170, 220, font, "Aspect ratio", 20, BLACK);
        	for (unsigned int i = 0; i < settings.size(); i++)
	        {
	    		settings[i].Render();
	        }
        }

        // Rectangle needed for the fading animation
        GRRLIB_Rectangle(0, 0, 640, 528, RGBA(0, 0, 0, alphaFadeRectangle), true);

        GRRLIB_Render();
    }

    // Game
    ResetPlatforms(platforms, platformSprite);

    // Needed to keep track of the delta y for platform and for delta score 
    int accumulator = 0;
    // Score
    int score = 0;
    // Value to keep track for the animations of the text after death
    int textPosY = 10;
    bool isDead = false;
    // C-Strings to keep score and best score
    char scoreStr[20];
    char bestScoreStr[20];
    sprintf(bestScoreStr, "Best: %d", highScore);

    // Set the player's initial position
    player.position.x = 200;

    // Loop forever
    while(1) {
    	// Scan the Wiimotes
        WPAD_ScanPads();  

        // Button press
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_2 && isDead) 
        {
        	// GRRLIB unlike other libraries like PyGame deletes the screen buffer after every render.
        	// We need to render everything even if we're doing only the fade animation
        	for (alphaFadeRectangle = 0; alphaFadeRectangle < 255; alphaFadeRectangle+=16)
        	{
        		background.Render();
        		GRRLIB_PrintfTTF((640 / 2) - GRRLIB_WidthTTF(font, "Game over!", 48) / 2, textPosY + 550, font, "Game over!", 48, 0xAA0000FF);
        		GRRLIB_PrintfTTF((640 / 2) - GRRLIB_WidthTTF(font, scoreStr, 36) / 2, textPosY + 625, font, scoreStr, 36, BLACK);
        		GRRLIB_PrintfTTF((640 / 2) - GRRLIB_WidthTTF(font, bestScoreStr, 30) / 2, textPosY + 675, font, bestScoreStr, 30, BLACK);
        		GRRLIB_DrawImg(320 - (56 * aspectRatioX), textPosY + 750, playAgainSprite, 0, aspectRatioX, 1, 0xE4A9B2FF);
        		GRRLIB_Rectangle(0, 0, 640, 528, RGBA(0, 0, 0, alphaFadeRectangle), true);
        		GRRLIB_Render();
        	}	
        	// Restart
        	score = 0;
		    ResetPlatforms(platforms, platformSprite);
		    player.Reset(Vector2(200, 380));
		    textPosY = 10;
		    isDead = false;
		    accumulator = 0;

        }
        // Move left
        if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP)
        {
            player.SetX(-player.velocity);

        }
        // Move right
        else if (WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN)
        {
            player.SetX(player.velocity);
        }
        // No movement if no arrow is pressed
        else 
        	player.SetX(0);

        // EndInput
        // Logic
        // The player is not dead
        if (!isDead)
        {
        	player.Update();
	        player.CheckCollisionWithPlatform(platforms);

	        // The player is on the upper part of the screen, stop moving him and scroll down the platforms
	        // Also add up score
	        if (player.position.y < 150)
	        {
	        	accumulator = !player.IsFalling() ? 150 - player.position.y : 0;
	        	player.position.y += accumulator;
	        	score += accumulator;
	        }
	        // Update platforms
	        for (unsigned int i = 0; i < platforms.size(); i++)
	        {
				platforms[i].position.y += accumulator;
				platforms[i].Update();
	        	platforms[i].Render();
	        }
	        // If the player falls under the screen end game loop
	        if (player.position.y > 470)
	        {
	        	isDead = true;
	        	if (score > highScore)
	        	{
	        		highScore = score;
		        	saveManager.Save(aspectRatioX, highScore);
		        	sprintf(bestScoreStr, "Best: %d", highScore);
	        	}
	        }
	        // Update score string
			sprintf(scoreStr, "Score: %d", score);
        }
        // The player is dead
        else
        {
        	// Use the accumulator variable to animate the platforms going up
        	accumulator = player.position.y - 470;
        	for (unsigned int i = 0; i < platforms.size(); i++)
        	{
        		if (platforms[i].position.y > -20)
        			platforms[i].position.y -= accumulator;
        	}
        	// The animation is not ended
        	if (textPosY > -450)
        	{
        		textPosY -= accumulator;
        		player.position.y -= accumulator;
        		player.Update();
        	}
        	// Animation is ended, make the player disappear
        	else
        	{
        		if (player.position.y < 528)
        			player.Update();
        	}
        }
		// EndLogic
        // Rendering
        GRRLIB_FillScreen(WHITE);
        background.Render();
        for (unsigned int i = 0; i < platforms.size(); i++)
        {
        	platforms[i].Render();
        }

        player.Render();

        GRRLIB_PrintfTTF(15, textPosY, font, scoreStr, 24, BLACK);
        GRRLIB_PrintfTTF(15, textPosY + 30, font, bestScoreStr, 18, 0x333333FF);
        GRRLIB_PrintfTTF((640 / 2) - GRRLIB_WidthTTF(font, "Game over!", 48) / 2, textPosY + 550, font, "Game over!", 48, 0xAA0000FF);
        GRRLIB_PrintfTTF((640 / 2) - GRRLIB_WidthTTF(font, scoreStr, 36) / 2, textPosY + 625, font, scoreStr, 36, BLACK);
        GRRLIB_PrintfTTF((640 / 2) - GRRLIB_WidthTTF(font, bestScoreStr, 30) / 2, textPosY + 675, font, bestScoreStr, 30, BLACK);
        // Doesn't use the base button class since it's animated
        GRRLIB_DrawImg(320 - (56 * aspectRatioX), textPosY + 750, playAgainSprite, 0, aspectRatioX, 1, 0xE4A9B2FF);

        if (alphaFadeRectangle > 0)
        	alphaFadeRectangle -= 16;
        GRRLIB_Rectangle(0, 0, 640, 528, RGBA(0, 0, 0, alphaFadeRectangle), true);
        // EndRendering
        GRRLIB_Render();
    }

    // Exit
    GRRLIB_Exit();
    exit(0);
}

// Reset platforms to a random position
void ResetPlatforms(std::vector<Platform>& _platforms, GRRLIB_texImg *_texture) {
	_platforms.clear();

	for (int i = 0; i < 11; i++)
    {
    	_platforms.push_back(Platform(static_cast<int>(rand() % 580), static_cast<int>(rand() % 15 + i * 40), _texture));
    }

    // Platform under the player
    _platforms.push_back(Platform(200, 460, _texture));
}

// Set aspect ratio
void SwitchAspectRatio(float ratio) {
	aspectRatioX = ratio;
}

// Given a button array, highlight a button
void HighlightButton(std::vector<Button>& _buttons, int _index) {
	for (unsigned int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].SetHighlighted(false);
	}
	_buttons[_index].SetHighlighted(true);
}

// Given a button array, set to the "selected" state a button
void SelectButton(std::vector<Button>& _buttons, int _index) {
	for (unsigned int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i].SetSelected(false);
	}
	_buttons[_index].SetSelected(true);
}
