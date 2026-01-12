#include "Game.h"

#include <iostream>
#include <fstream>

Game::Game(const std::string & config)
{
    init(config);
}

void Game::init(const std::string & path)
{
    std::ifstream fin(path);

    // fin >> m_playerConfig.SR >> m_playerConfig.CR >>

    m_window.create(sf::VideoMode({1280, 720}), "Assignment 2");
    m_window.setFramerateLimit(60);

    spawnPlayer();
}

void Game::run()
{
    while (m_running)
    {
        m_entities.update();

        if (!m_paused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
            sUserInput();
        }

        sRender();

        m_currentFrame++;
    }
}

void Game::setPaused(bool paused)
{

}

void Game::spawnPlayer()
{
    auto entity = m_entities.addEntity("player");

    float mx = m_window.getSize().x / 2.0f;
    float my = m_window.getSize().y / 2.0f;

    entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(0.0f, 0.0f), 0.0f);

    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

    entity->cInput = std::make_shared<CInput>();

    m_player = entity;
}

void Game::spawnEnemy()
{
    if (m_lastEnemySpawnTime <= m_currentFrame + 360)
    {
        auto entity = m_entities.addEntity("player");

        float ex = rand() % m_window.getSize().x;
        float ey = rand() % m_window.getSize().y;

        entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

        entity->cShape = std::make_shared<CShape>(16.0f, 8, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

        entity->cInput = std::make_shared<CInput>();
    }
    m_lastEnemySpawnTime = m_currentFrame;
}

void spawnSmallEnemies(std::shared_ptr<Entity> entity);
void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos);
void spawnSpecialWeapon(std::shared_ptr<Entity> entity);