#include "Input.h"

// Globals

EKeyState  g_aiKeyStates[MaxKeyCodes];

// Initialisation
void InitInput()
{
	// Initialise input data
	for (int i = 0; i < MaxKeyCodes; ++i)
	{
		g_aiKeyStates[i] = kNotPressed;
	}
}

// Events

// Event called to indicate that a key has been pressed down
void KeyDownEvent(KeyCodes eKeyCode)
{
	if (g_aiKeyStates[eKeyCode] == kNotPressed)
	{
		g_aiKeyStates[eKeyCode] = kPressed;
	}
	else
	{
		g_aiKeyStates[eKeyCode] = kHeld;
	}
}

// Event called to indicate that a key has been lifted up
void KeyUpEvent(KeyCodes eKeyCode)
{
	g_aiKeyStates[eKeyCode] = kNotPressed;
}

// Returns true when a given key or button is first pressed down.
bool KeyHit(KeyCodes eKeyCode)
{
	if (g_aiKeyStates[eKeyCode] == kPressed)
	{
		g_aiKeyStates[eKeyCode] = kHeld;
		return true;
	}
	return false;
}

// Returns true as long as a given key or button is held down.
bool KeyHeld(KeyCodes eKeyCode)
{
	if (g_aiKeyStates[eKeyCode] == kNotPressed)
	{
		return false;
	}
	g_aiKeyStates[eKeyCode] = kHeld;
	return true;
}