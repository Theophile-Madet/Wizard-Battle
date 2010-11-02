/*
 *  define.h
 *  WizardBattle
 */
#ifndef DEF_DEFINE
#define DEF_DEFINE

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define TILE_HEIGHT 171
#define TILE_WIDTH 101
#define TILE_UNUSED_HEIGHT 50
#define TILE_USED_HEIGHT 84
#define TILE_THICKNESS 37

#define RUNE_WIDTH 32
#define RUNE_HEIGHT 35

#define FLYINGSTAR_DAMAGE 10

#define TELEPORTATION_RANGE 500

enum Direction
{
	LEFT=0, UP=1, RIGHT=2, DOWN=3
};

enum RuneType
{
	RED, BLUE, GREEN, YELLOW, NONE
};

#endif