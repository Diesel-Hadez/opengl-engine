#ifndef PAUSABLE_H
#define PAUSABLE_H

class Pausable {
public:
    virtual void OnPause();
    virtual void OnResume();
    virtual ~Pausable() = default;
};

#endif
