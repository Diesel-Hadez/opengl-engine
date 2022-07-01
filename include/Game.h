#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;   
class Scene;
namespace reactphysics3d{
	class PhysicsCommon;
}
class GLFWwindow;
class Game {
private:
	using PhysicsCommon = reactphysics3d::PhysicsCommon;
	typedef std::unique_ptr<PhysicsCommon> PhysicsCommonPtr;
public:
	static PhysicsCommonPtr m_PhysicsCommon;
    static GLFWwindow* m_Window;
private:
    Game();
    void InitOpenGL();
	void InitImgui();
    void Loop();
public:
    std::vector<std::unique_ptr<Scene>> m_Scenes;
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
	static Game& GetInstance() 
	{
		static Game instance;
		return instance;
	}
	void Run();
	void PushScene(std::unique_ptr<Scene> pushed);
	void PopScene();
	~Game();
};

#endif
