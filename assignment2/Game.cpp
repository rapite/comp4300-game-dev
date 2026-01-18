#include "include/Game.h"

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
        
        sUserInput();
        
        if (!m_paused)
        {
            /*
            sEnemySpawner();
            sCollision();
            */
           sMovement();
        }

        sRender();

        m_currentFrame++;
    }
    m_window.close();
}

void Game::setPaused(bool paused)
{
    m_paused = paused;
}

void Game::sMovement()
{
    // Reset velocity each frame
    m_player->cTransform->velocity.x = 0;
    m_player->cTransform->velocity.y = 0;

    // Set velocity based on input (allows simultaneous keys)
    if (m_player->cInput->up)
        m_player->cTransform->velocity.y = -5;
    if (m_player->cInput->down)
        m_player->cTransform->velocity.y = 5;
    if (m_player->cInput->left)
        m_player->cTransform->velocity.x = -5;
    if (m_player->cInput->right)
        m_player->cTransform->velocity.x = 5;

    // Apply velocity to position
    m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
    m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
}

void Game::sUserInput()
{
    while (const std::optional event = m_window.pollEvent())
    {
        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPress->code == sf::Keyboard::Key::W)
            {
                m_player->cInput->up = true;
                std::cout << "Pressed Up" << "\n";
            }
            if (keyPress->code == sf::Keyboard::Key::A)
            {
                m_player->cInput->left = true;
                std::cout << "Pressed Left" << "\n";
            }
            if (keyPress->code == sf::Keyboard::Key::S)
            {
                m_player->cInput->down = true;
                std::cout << "Pressed Down" << "\n";
            }
            if (keyPress->code == sf::Keyboard::Key::D)
            {
                m_player->cInput->right = true;
                std::cout << "Pressed Right" << "\n";
            }
            if (keyPress->code == sf::Keyboard::Key::P)
            {
                setPaused(!m_paused);
            }

        }
        if (const auto* KeyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            if (KeyReleased->code == sf::Keyboard::Key::W)
            {
                m_player->cInput->up = false;
                std::cout << "Released Up" << "\n";
            }
            if (KeyReleased->code == sf::Keyboard::Key::A)
            {
                m_player->cInput->left = false;
                std::cout << "Released Left" << "\n";
            }
            if (KeyReleased->code == sf::Keyboard::Key::S)
            {
                m_player->cInput->down = false;
                std::cout << "Released Down" << "\n";
            }
            if (KeyReleased->code == sf::Keyboard::Key::D)
            {
                m_player->cInput->right = false;
                std::cout << "Released Right" << "\n";
            }
        }

        if (event->is<sf::Event::Closed>()){
            m_running = false;
        }
    }
}

void Game::sLifespan()
{

}

void Game::sRender()
{
    m_window.clear(sf::Color::Black);

    // std::cout << m_entities.getEntities().size() << '\n';

    for (auto e: m_entities.getEntities())
    {
        e->cShape->circle.setPosition({e->cTransform->pos.x, e->cTransform->pos.y});
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(sf::degrees(e->cTransform->angle));

        m_window.draw(e->cShape->circle);
    }
    m_window.display();
}

void Game::sEnemySpawner()
{

}

void Game::sCollision()
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

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{

}
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos)
{

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}