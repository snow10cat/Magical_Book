
#include "CatGameLib.h"
#include "Game/ResourceManager.h"
#include "Scene/SceneManager.h"

using namespace CatGameLib;
using namespace MagicalBook;

int main()
{
	//���C�u�����̃C���X�^���X�擾
	LibMain* const lib = LibMain::getInstance();

	//�X�N���[���T�C�Y�ݒ�
	lib -> setScreenSize(1280, 720);

	//�X�N���[�����[�h�w��
	lib -> setScreenMode(LibMain::ScreenMode::Window);

	//�E�B���h�E�^�C�g������
	lib -> setWindowTitle("Magical_Book");

	//�w�i�F�ݒ�
	lib -> setClearColor(200.0f, 200.0f, 200.0f, 255.0f);

	//���C�u����������
	lib -> initLib();

	//���ʃX�v���C�g�t�@�C���ǂݍ���
	ResourceManager::getInstance() -> loadResource();

	//SceneManager::getInstance() -> createScene(SceneManager::EditSelect);

	//���C�����[�v
	while(lib -> checkWindowState())
	{
		//��ʏ���
		lib -> clear();

		//�V�[���A�b�v�f�[�g
		SceneManager::getInstance() -> update();

		//�`��
		lib -> draw();
	}

	return 0;
}
