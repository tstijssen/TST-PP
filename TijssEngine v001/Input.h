#pragma once

#include "KeyDefines.h"

// Initialise the input system
void InitInput();

// Event called to indicate that a key has been pressed down
void KeyDownEvent(KeyCodes eKeyCode);

// Event called to indicate that a key has been lifted up
void KeyUpEvent(KeyCodes eKeyCode);

// Returns true when a given key or button is first pressed down.
bool KeyHit(KeyCodes eKeyCode);

// Returns true as long as a given key or button is held down.
bool KeyHeld(KeyCodes eKeyCode);