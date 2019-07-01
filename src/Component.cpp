#include <memory>

#include "Component.h"
#include "GameObject.h"

Component::Component(std::shared_ptr<GameObject> associated) : associated(associated) {}

Component::~Component() {}

void Component::NotifyCollision(GameObject& other) {
    (void)other;
}

void Component::Start() {}