#pragma once

#include <Collisions/SFTile.h>




class TestableSFTile : public SFTile
{
public:
	using SFTile::SFTile;

	void ForTestingMakeVolumeNull();

	std::shared_ptr<IDrawable> GetTextObject();

	void CallOriginalResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast);
	void CallOriginalResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast);
	void CallOriginalResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast);

	bool CallOriginalResolveObjectToSlopeTop(IDynamicGameObject* obj, float tFirst, float tLast);
	bool CallOriginalResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast);
	bool CallOriginalResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast);
	void CallOriginalResolveObjectToEdgeBounds(IDynamicGameObject* obj);

protected:

	void ResolveObjectToBoxTop(IDynamicGameObject* obj, float tFirst, float tLast) override;
	void ResolveObjectToBoxBottom(IDynamicGameObject* obj, float tFirst, float tLast) override;
	void ResolveObjectToBoxHorizontally(IDynamicGameObject* obj, float tFirst, float tLast) override;

	bool ResolveObjectToSlopeTop(IDynamicGameObject* obj, float tFirst, float tLast) override;
	bool ResolveObjectToSlopeIncline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast) override;
	bool ResolveObjectToSlopeDecline(IDynamicGameObject* obj, int start, int end, float tFirst, float tLast) override;
	void ResolveObjectToEdgeBounds(IDynamicGameObject* obj) override;

public:

	bool boxTopCalled = false;
	bool boxBottomCalled = false;
	bool boxHorizontalCalled = false;

	bool slopeTopCalled = false;
	bool slopeTopResult = false;

	bool slopeInclineCalled = false;
	bool slopeInclineResult = false;

	bool slopeDeclineCalled = false;
	bool slopeDeclineResult = false;

	bool edgeBoundsCalled = false;
};