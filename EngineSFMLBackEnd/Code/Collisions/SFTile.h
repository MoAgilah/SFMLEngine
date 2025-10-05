#pragma once

#include <Engine/Interface/Collisions/ITile.h>
#include <Utilities/Vector.h>
#include <string>

class SFTile : public ITile
{
public:
	SFTile();
	SFTile(int gX, int gY, const std::string& fontName);

	void Render(IRenderer* renderer) override;
	void ResolveCollision(IDynamicGameObject* obj) override;

	void SetPosition(const Vector2f& pos) override;

	void SetFillColour(Colour col) override;
	void SetOutlineColour(Colour col) override;

protected:

	void ResolveObjectToBoxTop(IDynamicGameObject* obj) override;
	void ResolveObjectToBoxBottom(IDynamicGameObject* obj) override;
	void ResolveObjectToBoxHorizontally(IDynamicGameObject* obj) override;
	bool ResolveObjectToSlopeTop(IDynamicGameObject* obj) override;
	bool ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end) override;
	bool ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end) override;
	void ResolveObjectToEdgeBounds(IDynamicGameObject* obj) override;
};