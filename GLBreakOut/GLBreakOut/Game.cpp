#include "Game.h"

SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
{
}

Game::~Game()
{
	delete Renderer;

}

void Game::Init()
{
	ResourceManager::LoadShader("../shaders/vertexSpriteShader.vs", "../shaders/fragmentSpriteShader.fs", nullptr, "sprite");
	Shader spriteShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(spriteShader);

	ResourceManager::LoadTexture("../resource/textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("../resource/textures/background.jpg", false, "face");
	ResourceManager::LoadTexture("../resource/textures/background.jpg", false, "block");
	ResourceManager::LoadTexture("../resource/textures/background.jpg", false, "block_solid");

	GameLevel one;
	one.Load("../resource/Levels/one.lvl", this->Width, this->Height / 2);
	this->Levels.push_back(one);
	this->Level = 0;
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE) {
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		this->Levels[this->Level].Draw(*Renderer);
	}

}
