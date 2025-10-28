#include "SFMenuItem.h"

#include "../Drawables/SFShape.h"
#include <Utilities/Utils.h>

SFMenuItem::SFMenuItem(const Vector2f& menuSize, float outlineThickness)
{
	m_cellSpace = std::make_shared<SFRect>(menuSize, Vector2f());
	ENSURE_VALID(m_cellSpace);

	auto rect = dynamic_cast<SFRect*>(m_cellSpace.get());
	if (rect)
	{
		rect->SetScale({ 1.f, 1.f });
		rect->SetOrigin(Vector2f(rect->GetSize()) / 2.f);
		rect->SetOutlineThickness(outlineThickness);
		rect->SetOutlineColour(Colour::Green);
	}
}

Vector2f SFMenuItem::GetPosition() const
{
	ENSURE_VALID_RET(m_cellSpace, Vector2f());
	return static_cast<SFRect*>(m_cellSpace.get())->GetPosition();
}

void SFMenuItem::SetPosition(const Vector2f& position)
{
	ENSURE_VALID(m_cellSpace);
	static_cast<SFRect*>(m_cellSpace.get())->SetPosition(position);
}

Vector2f SFMenuItem::GetOrigin() const
{
	ENSURE_VALID_RET(m_cellSpace, Vector2f());
	return static_cast<SFRect*>(m_cellSpace.get())->GetOrigin();
}

Vector2f SFMenuItem::GetSize() const
{
	ENSURE_VALID_RET(m_cellSpace, Vector2f());
	return static_cast<SFRect*>(m_cellSpace.get())->GetSize();
}

IText* SFMenuItem::AddTextElement(std::shared_ptr<IText> text)
{
	ENSURE_VALID_RET(text, nullptr);
	m_textElement = std::move(text);     // stores as shared_ptr<IText>
	return m_textElement.get();
}

ISprite* SFMenuItem::AddSpriteElement(std::shared_ptr<ISprite> spr)
{
	ENSURE_VALID_RET(spr, nullptr);
	m_spriteElement = std::move(spr);
	return m_spriteElement.get();
}