#include "Game.h"

SpriteRenderer* Renderer;
GameObject* Player;
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

Game::Game(unsigned int width, unsigned int height)
	:Width(width), Height(height), State(GAME_ACTIVE)
{
}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	ResourceManager::LoadShader("../shaders/vertexSpriteShader.vs", "../shaders/fragmentSpriteShader.fs", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	Shader spriteShader = ResourceManager::GetShader("sprite");
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);

	Renderer = new SpriteRenderer(spriteShader);

    ResourceManager::LoadTexture("../resources/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("../resources/textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("../resources/textures/block.png", false, "block");
    ResourceManager::LoadTexture("../resources/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("../resources/textures/paddle.png", true, "paddle");

	GameLevel one;
	one.Load("../resources/levels/one.lvl", this->Width, this->Height / 2);
	this->Levels.push_back(one);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2(
		this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->Height - PLAYER_SIZE.y
	);

	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

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
		Player->Draw(*Renderer);
	}

}
