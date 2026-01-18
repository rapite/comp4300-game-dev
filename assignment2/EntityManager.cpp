#include "include/EntityManager.h"

void EntityManager::update()
{
    for (auto& e: m_toAdd)
    {
       m_entities.push_back(e); 
       m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

    // TODO: Implement entity removals based on "dead"
    for (auto& e: m_entities)
    {
        
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_toAdd.push_back(e);
    return e;
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}