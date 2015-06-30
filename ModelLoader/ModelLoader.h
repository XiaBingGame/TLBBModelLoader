/*
-----------------------------------------------------------------------------
Filename:    ModelLoader.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#ifndef __ModelLoader_h_
#define __ModelLoader_h_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class ModelLoader : public BaseApplication
{
public:
    ModelLoader(void);
    virtual ~ModelLoader(void);

protected:
    virtual void createScene(void);
	bool keyPressed(const OIS::KeyEvent &arg);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	void changeIndex();

	std::vector<Ogre::SceneNode*> mModelNodes;

	unsigned int mIndex;
	unsigned int mMeshCount;
	std::vector<Ogre::AnimationState*> m_Anim1;
	std::vector<Ogre::AnimationState*> m_Anim2;
	std::vector<Ogre::AnimationState*> m_Anim3;
};

//---------------------------------------------------------------------------

#endif // #ifndef __ModelLoader_h_

//---------------------------------------------------------------------------
