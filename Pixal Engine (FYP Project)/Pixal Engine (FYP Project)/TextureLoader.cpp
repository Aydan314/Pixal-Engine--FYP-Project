#include "TextureLoader.h"
TextureLoader* TextureLoader::m_instance = nullptr;

void TextureLoader::loadSurfaces()
{
	// Iterates through all the specified textures and stores them for game objects to reference //
	for (auto& item : TEXTURES_TO_LOAD)
	{
		std::string textureName = item.name;
		Vector2D size = item.cellAmount;
		SDL_Texture* texture;

		SDL_Surface* p_surface = IMG_Load(textureName.c_str());

		if (p_surface != nullptr)
		{
			texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);

			SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0, 0));

			if (texture == nullptr)
			{
				std::cout << "!! Unable to create texture from surface. Error: " << SDL_GetError() << "!!\n";
			}
			else
			{
				m_loadedSurfaces.push_back({ item.name,Vector2D(p_surface->w, p_surface->h), texture });
			}

			SDL_FreeSurface(p_surface);

		}
		else
		{
			std::cout << "!! Unable to create texture from surface. Error: " << SDL_GetError() << "!!\n";
		}

	}
}

void TextureLoader::loadGameSurfaces()
{
	// Iterates through all the specified textures and stores them for game objects to reference //
	for (auto& item : TEXTURES_TO_LOAD)
	{
		std::string textureName = item.name;
		Vector2D size = item.cellAmount;
		SDL_Texture* texture;

		SDL_Surface* p_surface = IMG_Load(textureName.c_str());

		if (p_surface != nullptr)
		{
			texture = SDL_CreateTextureFromSurface(m_gameRenderer, p_surface);

			SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0, 0));

			if (texture == nullptr)
			{
				std::cout << "!! Unable to create texture from surface. Error: " << SDL_GetError() << "!!\n";
			}
			else
			{
				m_gameLoadedSurfaces.push_back({ item.name,Vector2D(p_surface->w, p_surface->h), texture });
			}

			SDL_FreeSurface(p_surface);

		}
		else
		{
			std::cout << "!! Unable to create texture from surface. Error: " << SDL_GetError() << "!!\n";
		}

	}
}

TextureLoader::TextureLoader(SDL_Renderer* renderer)
{
	m_renderer = renderer;
	loadSurfaces();
}

TextureLoader::~TextureLoader()
{
	m_instance = nullptr;

	delete m_renderer;
	m_renderer = nullptr;
}

TextureData TextureLoader::GetTexture(std::string name)
{
	for (auto item : m_loadedSurfaces)
	{
		if (item.path == name) return item;
	}
	std::cout << "!! Unable to find " << name << " !!\n";
	return TextureData();
}

TextureData TextureLoader::GetGameTexture(std::string name)
{
	for (auto item : m_gameLoadedSurfaces)
	{
		if (item.path == name) return item;
	}
	std::cout << "!! Unable to find " << name << " !!\n";
	return TextureData();
}

SDL_Renderer* TextureLoader::GetRenderer()
{
	return m_renderer;
}

TextureLoader* TextureLoader::Instance(SDL_Renderer* renderer)
{
	if (!m_instance)
	{
		m_instance = new TextureLoader(renderer);
	}
	return m_instance;
}

void TextureLoader::SetGameRenderer(SDL_Renderer* renderer)
{
	m_gameRenderer = renderer;
	loadGameSurfaces();
}
