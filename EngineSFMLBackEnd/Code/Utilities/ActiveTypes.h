#pragma once
#include <Utilities/Defines.h>
#if USE_SFML

#include "../Resources/SFFont.h"
#include "../Resources/SFShader.h"
#include "../Resources/SFTexture.h"
#include "../Resources/SFMusic.h"
#include "../Resources/SFSound.h"

// Repeat the aliases here with complete types available
using ActiveFont = SFFont;
using ActiveShader = SFShader;
using ActiveTexture = SFTexture;
using ActiveMusic = SFMusic;
using ActiveSound = SFSound;
#endif
