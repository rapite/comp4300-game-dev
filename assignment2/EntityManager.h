#pragma once

#include <map>
#include <string>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec>     EntityMap;

class EntityManager
{
  EntityVec m_entities;
  EntityMap m_entityMap;
  size_t m_totalEntities = 0;
  public:
    EntityManager();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    void update();
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
};
