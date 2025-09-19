#pragma once

#include <Engine/Interface/Renderer/IRenderer.h>
#include <Utilities/Vector.h>
#include <string>

class IRenderable; // fwd-declare

class SFRenderer : public IRenderer
{
public:
    void Initialise(const Vector2f& screenDims, const std::string& title) override;
    void PollWindowEvents() override;
    void Clear() override;
    void Draw(IRenderable* object) override;
    void Present() override;

private:

    // Cache the native handle (type-erased) to avoid calling GetNativeHandle() every frame
    void* m_nativeWindow = nullptr;
};
