#ifndef SCENE_H
#define SCENE_H
#include <string>
#include "Pausable.h"

class Scene: public Pausable
{
protected:
public:
	std::string m_SceneName;
	bool m_End;
	virtual void Update() = 0;
	virtual void Render() = 0;
	
	virtual void OnPause() override;
	virtual void OnResume() override;
	Scene();
	virtual ~Scene();
};
#endif

