#pragma once

/**
 * Instruction class of the Doom application.
 */
#define CLA 0xD0

/**
 * Parameter 2 for last APDU to receive.
 */
#define P2_LAST 0x00
/**
 * Parameter 2 for more APDU to receive.
 */
#define P2_MORE 0x80
/**
 * Parameter 1 for first APDU number.
 */
#define P1_START 0x00
/**
 * Parameter 1 for maximum APDU number.
 */
#define P1_MAX 0x03

/**
 * Enumeration with expected INS of APDU commands.
 */
typedef enum {
    GET_VERSION = 0x03,   /// version of the application
    GET_APP_NAME = 0x04,  /// name of the application
    DOOM = 0x0D,          /// doom commands
} command_e;


/**
 * Enumeration with expected PARAMETER of Doom APDU command.
 */
typedef enum {
    INPUT = 0x05,       /// send input
    QUIT = 0x06,        /// quit/pause the game 
    DOOMIT = 0x07,      /// start/resume new game
} command_parameter;

/**
 * Enumeration with expected DATA of DOOM INPUT command.
 */
typedef enum {
    UP = 0x05,  
    DOWN = 0x06,
    LEFT = 0x07,
    RIGHT = 0x8,
    FIRE = 0x0F 
} controls;
