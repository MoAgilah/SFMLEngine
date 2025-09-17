#include "SFMenuItem.h"

#include "../Drawables/SFShape.h"

SFMenuItem::SFMenuItem(const Vector2f& menuSize, float outlineThickness)
{
	m_cellSpace = std::make_shared<SFRect>(menuSize, Vector2f());
	auto rect = dynamic_cast<SFRect*>(m_cellSpace.get());
	if (rect)
	{
		rect->SetOrigin(Vector2f(rect->GetSize()) / 2.f);
		rect->SetOutlineThickness(outlineThickness);
		rect->SetOutlineColour(Colour::Green);
	}
}

Vector2f SFMenuItem::GetPosition() const
{
	return static_cast<SFRect*>(m_cellSpace.get())->GetPosition();
}

void SFMenuItem::SetPosition(const Vector2f& position)
{
	static_cast<SFRect*>(m_cellSpace.get())->SetPosition(position);
}

Vector2f SFMenuItem::GetOrigin() const
{
	return static_cast<SFRect*>(m_cellSpace.get())->GetOrigin();
}

Vector2f SFMenuItem::GetSize() const
{
	return static_cast<SFRect*>(m_cellSpace.get())->GetSize();
}

IText* SFMenuItem::AddTextElement(std::shared_ptr<IText> text)
{
	m_textElement = std::move(text);     // stores as shared_ptr<IText>
	return m_textElement.get();
}

ISprite* SFMenuItem::AddSpriteElement(std::shared_ptr<ISprite> spr)
{
	m_spriteElement = std::move(spr);
	return m_spriteElement.get();
}