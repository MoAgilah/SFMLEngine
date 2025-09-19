#include <memory>

#include <Utilities/ActiveTypesFwd.h>
#include "ActiveTypes.h"  // pulls in SFFont/SFShader/etc when USE_SFML

#if USE_SFML
std::unique_ptr<IFont>    MakeActiveFont() { return std::make_unique<ActiveFont>(); }
std::unique_ptr<IMusic>   MakeActiveMusic() { return std::make_unique<ActiveMusic>(); }
std::unique_ptr<ISound>   MakeActiveSound() { return std::make_unique<ActiveSound>(); }
std::unique_ptr<IShader>  MakeActiveShader() { return std::make_unique<ActiveShader>(); }
std::unique_ptr<ITexture> MakeActiveTexture() { return std::make_unique<ActiveTexture>(); }
#else
// (Optional) non-SFML implementations
#endif
