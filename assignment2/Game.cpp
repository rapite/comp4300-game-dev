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
            //sCollisoin
            sLifespan();
            sEnemySpawner();
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

    for (auto& e : m_entities.getEntities("bullet")) {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }
}

void Game::sUserInput()
{
    while (const std::optional event = m_window.pollEvent())
    {
        // Keyboard Events
        if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>())
        {
            switch (keyPress->code)
            {
            case sf::Keyboard::Key::W:
                m_player->cInput->up = true;
                std::cout << "Pressed Up" << "\n";
                break;
            case sf::Keyboard::Key::A:
                m_player->cInput->left = true;
                std::cout << "Pressed Left" << "\n";
                break;
            case sf::Keyboard::Key::S:
                m_player->cInput->down = true;
                std::cout << "Pressed Down" << "\n";
                break;
            case sf::Keyboard::Key::D:
                m_player->cInput->right = true;
                std::cout << "Pressed Right" << "\n";
                break;
            case sf::Keyboard::Key::P:
                setPaused(!m_paused);
            default:
                break;
            }
        }
        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            switch (keyReleased->code)
            {
            case sf::Keyboard::Key::W:
                m_player->cInput->up = false;
                std::cout << "Released Up" << "\n";
                break;
            case sf::Keyboard::Key::A:
                m_player->cInput->left = false;
                std::cout << "Released Left" << "\n";
                break;
            case sf::Keyboard::Key::S:
                m_player->cInput->down = false;
                std::cout << "Released Down" << "\n";
                break;
            case sf::Keyboard::Key::D:
                m_player->cInput->right = false;
                std::cout << "Released Right" << "\n";
                break;
            default:
                break;
            }
        }

        // Mouse Events
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "Left Mouse(" << mouseButtonPressed->position.x
                    << ", " << mouseButtonPressed->position.y << ")\n";
                // Shoot

                Vec2 mousePosition(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                spawnBullet(m_player, mousePosition); 
            }
        }
        // Close
        if (event->is<sf::Event::Closed>()){
            m_running = false;
        }
    }
}

void Game::sLifespan()
{
    for (auto& e : m_entities.getEntities())
    {
        if (e->cLifespan)
        {
            if (e->cLifespan->remaining <= 0)
                e->destroy();
                else e->cLifespan->remaining--;
        }
    }
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
    if (m_currentFrame - m_lastEnemySpawnTime > 360)
    {
        spawnEnemy();
    }
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
    auto entity = m_entities.addEntity("enemy");

    float ex = rand() % m_window.getSize().x;
    float ey = rand() % m_window.getSize().y;

    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0.0f, 0.0f), 0.0f);

    entity->cShape = std::make_shared<CShape>(16.0f, 12, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);

    entity->cInput = std::make_shared<CInput>();

    m_lastEnemySpawnTime = m_currentFrame;
}

// Spawn little ones when big one explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos)
{
    float dX = mousePos.x - entity->cTransform->pos.x;
    float dY = mousePos.y - entity->cTransform->pos.y;

    float h = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));

    auto bullet = m_entities.addEntity("bullet");
    float speed = 3;

    bullet->cTransform = std::make_shared<CTransform>(
        Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y),
        Vec2(speed*dX/h, speed*dY/h), 0.0f);

    std::cout << "New Bullet: " << dX/h << ", " << dY/h << "\n";

    bullet->cShape = std::make_shared<CShape>(
        4.0f, 5, sf::Color(255, 255, 255),
        sf::Color(255, 255, 255), 4.0f);

    bullet->cLifespan = std::make_shared<CLifespan>(180);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}