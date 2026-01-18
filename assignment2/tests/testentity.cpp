#include "../include/Game.h"

int main()
{
    EntityManager em;
    em.addEntity("coc");
    auto all_e = em.getEntities();
    EntityVec e = em.getEntities("coc");
    Vec2 p(100, 200), v(10, 10);
    e[0]->cTransform = std::make_shared<CTransform>(p,v, 50.f);
}
