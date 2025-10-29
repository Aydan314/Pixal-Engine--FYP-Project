#include "Texture2D.h"

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	m_columns = 0;
	m_rows = 0;

	m_height = 0;
	m_width = 0;
	m_texture = nullptr;
}

Texture2D::~Texture2D()
{
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadStoredTexture(std::string path, int columns, int rows)
{
	Free();

	// Loads the image //
	TextureData textureData;

	textureData = TextureLoader::Instance(m_renderer)->GetTexture(path);

	// Defines texture values //
	m_texture = textureData.texture;

	m_columns = columns;
	m_rows = rows;

	m_width = textureData.size.x / m_columns;
	m_height = textureData.size.y / m_rows;

	return m_texture != nullptr;

}

void Texture2D::Free()
{
	// Resets texture values and destroys texture //
	if (m_texture != nullptr)
	{
		//SDL_DestroyTexture(m_texture);
		m_texture = nullptr;

		m_width = 0;
		m_height = 0;
		m_columns = 0;
		m_rows = 0;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, int columnNum, int rowNum, double angle, Vector2D scale, SDL_Color colour)
{
	// Renders the specified cell of the sprite sheet //
	SDL_Rect spriteSheetRect = { m_width * columnNum, m_height * rowNum,m_width,m_height };
	SDL_Rect renderLocation = { m_renderOffset.x + new_position.x,new_position.y + m_renderOffset.y,m_width * scale.x,m_height * scale.y };
	SDL_Point renderCentre = { m_width / 2 * scale.x, m_height / 2 * scale.y };

	if (colour.a > 0) SDL_SetTextureColorMod(m_texture, colour.r, colour.g, colour.b);

	SDL_RenderCopyEx(m_renderer, m_texture, &spriteSheetRect, &renderLocation, angle, &renderCentre, flip);

	// Checks for errors //
	if (columnNum >= m_columns || rowNum >= m_rows)
	{
		std::cout << "!! Invalid cell selection !!\n";
	}
}

void Texture2D::SetRenderOffset(Vector2D offset)
{
	m_renderOffset = offset;
}

void Texture2D::SetRenderColour(SDL_Color colour)
{
	SDL_SetTextureColorMod(m_texture, colour.r, colour.g, colour.b);
	m_colour = colour;
}

