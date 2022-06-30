#ifndef CAMERAINPUTHANDLER_H
#define CAMERAINPUTHANDLER_H

class FPCamera;
class Command;
class Scene;
class CameraInputHandler {
private:
    typedef int Key;
    FPCamera* m_Camera;
    Scene * m_Scene;
    
    Command* m_CommandForward;
    Command* m_CommandBackward;
    Command* m_CommandLeft;
    Command* m_CommandRight;
    Command* m_CommandUp;
    Command* m_CommandDown;
    
    Key m_KeyForward;
    Key m_KeyBackward;
    Key m_KeyLeft;
    Key m_KeyRight;
    Key m_KeyUp;
    Key m_KeyDown;
public:
    void HandleInputs(float deltaTime);
    CameraInputHandler(Scene* scene, FPCamera* camera);
    ~CameraInputHandler();
};

#endif
