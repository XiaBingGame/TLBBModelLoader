/*
-----------------------------------------------------------------------------
Filename:    ModelLoader.cpp
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

#include "ModelLoader.h"
#include <OgreEntity.h>
using namespace Ogre;
//---------------------------------------------------------------------------
ModelLoader::ModelLoader(void) :
	mIndex(0), mMeshCount(0)
{

}
//---------------------------------------------------------------------------
ModelLoader::~ModelLoader(void)
{
}
bool ModelLoader::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(m_Anim1.size() == m_Anim2.size() && m_Anim1.size() > 0 && m_Anim2.size() > 0 && mIndex < m_Anim1.size() && mIndex < m_Anim2.size())
	{
		m_Anim1[mIndex]->addTime(evt.timeSinceLastFrame);
		m_Anim2[mIndex]->addTime(evt.timeSinceLastFrame);
		if(mMeshCount == 3)
		{
			m_Anim3[mIndex]->addTime(evt.timeSinceLastFrame);
		}
	}
	return BaseApplication::frameRenderingQueued(evt);
}
//---------------------------------------------------------------------------
bool ModelLoader::keyPressed(const OIS::KeyEvent &arg)
{
	if(arg.key == OIS::KC_SPACE && m_Anim1.size() == m_Anim2.size() && m_Anim1.size() > 0 && m_Anim2.size() > 0 && mIndex < m_Anim1.size() && mIndex < m_Anim2.size())
	{
		changeIndex();
	}
	
	return BaseApplication::keyPressed(arg);
}
//---------------------------------------------------------------------------
void ModelLoader::createScene(void)
{
    // Create your scene here :)
	mSceneMgr->setAmbientLight(ColourValue(0.3f, 0.3f, 0.3f));
	mSceneMgr->createLight()->setPosition(20, 80, 50);

	// mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox"); 

	Ogre::String s = "狼人神汉";
	mMeshCount = 2;
	// Ogre::String s = "残破兵俑";
	// mMeshCount = 3;
	Entity* mEntity1 = mSceneMgr->createEntity(s + "头.mesh");
	mEntity1->setMaterialName(s + "头");
	SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		Ogre::Vector3(0, 0, 25.0));
	mNode->attachObject(mEntity1);
	Entity* mEntity2 = mSceneMgr->createEntity(s + "身.mesh");
	mEntity2->setMaterialName(s + "身");
	mNode->attachObject(mEntity2);
	Entity* mEntity3;
	if(mMeshCount == 3)
	{
		mEntity3 = mSceneMgr->createEntity(s + "剑.mesh");
		mEntity3->setMaterialName(s + "剑");
		mNode->attachObject(mEntity3);
	}
	
	AnimationStateSet* animationStateSet = mEntity1->getAllAnimationStates();
	AnimationStateIterator it = animationStateSet->getAnimationStateIterator();
	while (it.hasMoreElements())
	{
		AnimationState* a = it.getNext();
		m_Anim1.push_back(a);
	}

	animationStateSet = mEntity2->getAllAnimationStates();
	it = animationStateSet->getAnimationStateIterator();
	while (it.hasMoreElements())
	{
		AnimationState* a = it.getNext();
		m_Anim2.push_back(a);
	}

	if (mMeshCount == 3)
	{
		animationStateSet = mEntity3->getAllAnimationStates();
		it = animationStateSet->getAnimationStateIterator();
		while (it.hasMoreElements())
		{
			AnimationState* a = it.getNext();
			m_Anim3.push_back(a);
		}
	}

	changeIndex();

	mCamera->setPosition(Ogre::Vector3(0,50,400));
}

void ModelLoader::changeIndex()
{
	if(m_Anim1.size() == m_Anim2.size() && m_Anim1.size() > 0 && m_Anim2.size() > 0 && mIndex < m_Anim1.size() && mIndex < m_Anim2.size())
	{
		m_Anim1[mIndex]->setEnabled(false);
		m_Anim1[mIndex]->setLoop(false);
		m_Anim2[mIndex]->setEnabled(false);
		m_Anim2[mIndex]->setLoop(false);
		if(mMeshCount == 3)
		{
			m_Anim3[mIndex]->setEnabled(false);
			m_Anim3[mIndex]->setLoop(false);
		}
		mIndex = (mIndex+1) % m_Anim1.size();
		m_Anim1[mIndex]->setEnabled(true);
		m_Anim1[mIndex]->setLoop(true);
		m_Anim2[mIndex]->setEnabled(true);
		m_Anim2[mIndex]->setLoop(true);
		if(mMeshCount == 3)
		{
			m_Anim3[mIndex]->setEnabled(true);
			m_Anim3[mIndex]->setLoop(true);
		}
	}
}
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        ModelLoader app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
