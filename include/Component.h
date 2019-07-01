#pragma once

#include <string>
#include <memory>

class GameObject;

class Component{
public:
    Component(std::shared_ptr<GameObject> associated);
    virtual ~Component();
    void virtual Update(int dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(const std::string& type) = 0;
    void virtual NotifyCollision(GameObject& other);
    void virtual Start();
    std::shared_ptr<GameObject> associated;
};

