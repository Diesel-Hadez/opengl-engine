#ifndef COMMAND_H
#define COMMAND_H

class Scene;
class Command {
public:
    virtual void execute(Scene* scene, float deltaTime)=0;
    
    virtual ~Command() = default;
};

#endif
