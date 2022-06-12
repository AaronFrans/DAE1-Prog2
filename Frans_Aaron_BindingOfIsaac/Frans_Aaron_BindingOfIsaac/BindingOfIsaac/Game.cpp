#include "pch.h"
#include "Game.h"
#include "Isaac.h"
#include "Poop.h"
#include "RoomManager.h"
#include "TearManager.h"
#include "IsaacHealthBar.h"
#include "UIManager.h"
#include "Room.h"
#include "Floor.h"
#include "ItemManager.h"
#include "Monstro.h"
#include "Minimap.h"
#include "SoundStream.h"
#include "SoundEffectManager.h"
#include "EnemyManager.h"
#include "MenuScreen.h"
#include "SoundEffect.h"
#include "PickUp.h"
#include "PickUpManager.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_TextureManager{}
	, m_Camera{ m_Window.width, m_Window.height }
	, m_State{ GameState::startMenu }
	, m_DeathScreenSfxAccuTime{ 0 }
	, m_DeathScreenSfxMaxTime{ 1.5f }

{

	Initialize();

}
Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_IsDeathScreenSfxPlaying = false;

	m_pSoundEffectManager = new SoundEffectManager{};
	m_pEnemyManager = new EnemyManager{ m_TextureManager, m_pSoundEffectManager };
	IsaacHealthBar* isaacHealthBar = new IsaacHealthBar(m_TextureManager.GetTexture(TextureManager::TextureLookup::uiHearths),
		3, Point2f{ m_Window.width / 2.0f, m_Window.height / 2.0f });
	InitPlayer(isaacHealthBar);
	InitTearManager();
	m_pRoomManager = new RoomManager{ m_TextureManager, m_pSoundEffectManager };
	m_pItemManager = new ItemManager{ m_TextureManager };
	InitFloor(m_pRoomManager);
	InitUIManager(isaacHealthBar);
	isaacHealthBar = nullptr;
	m_Camera.SetLevelBoundaries(m_pFloor->GetCurrentRoom()->GetBoundaries());

	m_pStartScreen = new MenuScreen{
		m_TextureManager.GetTexture(TextureManager::TextureLookup::startMenu),
		"Press ENTER to start the game",
		"Resources/Fonts/upheavtt.ttf",
		Rectf{0,0,m_Window.width, m_Window.height}
	};

	m_pDeathScreen = new MenuScreen{
		m_TextureManager.GetTexture(TextureManager::TextureLookup::deathScreen),
		"Press ENTER to restart the game",
		"Resources/Fonts/upheavtt.ttf",
		Rectf{0,0,m_Window.width, m_Window.height}
	};

	m_pVictoryScreen = new MenuScreen{
		m_TextureManager.GetTexture(TextureManager::TextureLookup::victoryScreen),
		"Press Enter to play again",
		"Resources/Fonts/upheavtt.ttf",
		Rectf{0,0,m_Window.width, m_Window.height}
	};

	SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::titleScreen) };
	track->SetVolume(15);
	track->Play(true);

	test = new PickUpManager{};

	std::cout << "Press I for the controlls.\n";
}

void Game::Cleanup()
{
	delete m_pRoomManager;
	delete m_pItemManager;
	delete m_pSoundEffectManager;
	delete m_pEnemyManager;
	delete m_pStartScreen;
	delete m_pDeathScreen;
	delete m_pVictoryScreen;
	DeleteTearManager();
	DeletePlayer();
	DeleteUIManager();
	DeleteFloor();
}

void Game::Update(float elapsedSec)
{

	switch (m_State)
	{
	case Game::GameState::playing:
		if (!m_pFloor->IsTransitioning())
		{
			UpdateTearManager(elapsedSec);
			UpdatePlayer(elapsedSec);
			m_pFloor->Update(elapsedSec, m_pPlayer, m_pTearManager, m_TextureManager);
			if (m_pPlayer->GetDamageState() == Isaac::DamageState::dead)
			{
				m_State = GameState::death;

				SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::deathScreen) };
				track->Stop();

				SoundEffect* sfx{ m_pSoundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::gameOverScreen) };
				sfx->StopAll();
				sfx->SetVolume(15);
				sfx->Play(0);
				m_IsDeathScreenSfxPlaying = true;
			}
			Room* pCurrentRoom{ m_pFloor->GetCurrentRoom() };
			if (!pCurrentRoom->HasDroppedPickUp() &&
				pCurrentRoom->GetType() == Room::RoomType::normal &&
				pCurrentRoom->IsCleared())
			{

				pCurrentRoom->DropPickUp();
				test->AddPickUp(pCurrentRoom, m_TextureManager);
			}
			if (pCurrentRoom->IsBossDead())
			{
				SoundEffect* sfx{ m_pSoundEffectManager->GetSoundEffect(SoundEffectManager::SoundEffectLookup::deathSplatter1) };
				sfx->StopAll();
				SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::victoryScreen) };
				track->Play(true);
				m_State = GameState::victory;
			}
			test->Update(pCurrentRoom, m_pPlayer);
		}
		else
		{
			m_Camera.SetLevelBoundaries(m_pFloor->GetCurrentRoom()->GetBoundaries());
			Room* pCurrentRoom{ m_pFloor->GetCurrentRoom() };
			if (m_pFloor->GetCurrentRoom()->GetType() == Room::RoomType::boss)
			{
				m_pUIManager->SetBossHealthBar(pCurrentRoom->GetBossHealthBar());
				SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::bossFight) };
				track->SetVolume(15);
				track->Play(true);
			}
			else
			{
				m_pUIManager->SetBossHealthBar(nullptr);
				SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::basementTrack) };
				if (!track->IsPlaying())
				{
					track->SetVolume(15);
					track->Play(true);
				}
			}
			m_pTearManager->ClearTears();
			m_pUIManager->UpdateMinimap(m_pFloor->GetCurrentIndexes());
			m_pFloor->DoneTransitioning();
		}
		break;
	case Game::GameState::death:

		if (m_IsDeathScreenSfxPlaying)
		{
			m_DeathScreenSfxAccuTime += elapsedSec;
			if (m_DeathScreenSfxAccuTime >= m_DeathScreenSfxMaxTime)
			{
				m_IsDeathScreenSfxPlaying = false;
			}
		}
		else
		{
			SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::deathScreen) };
			if (!track->IsPlaying())
			{
				track->Play(true);
			}
		}

	}


}

void Game::Draw() const
{

	ClearBackground();
	switch (m_State)
	{
	case Game::GameState::startMenu:

		m_pStartScreen->Draw();

		break;
	case Game::GameState::playing:
		glPushMatrix();
		m_Camera.Transform(m_pPlayer->GetCenter());
		DrawFloor();
		test->DrawPickups(m_pFloor->GetCurrentRoom());
		m_pTearManager->DrawBackTears();
		DrawPlayer();
		m_pTearManager->DrawFrontTears();
		DrawUIManager();
		glPopMatrix();
		break;
	case Game::GameState::death:
		m_pDeathScreen->Draw();
		break;
	case Game::GameState::victory:
		m_pVictoryScreen->Draw();
		break;
	default:
		break;
	}


}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.scancode)
	{
	case SDL_SCANCODE_KP_2:
		m_pPlayer->TakeDamage(0.5f);
		break;
	case SDL_SCANCODE_KP_3:
		m_pPlayer->TakeDamage(1.0f);
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (m_State)
	{
	case Game::GameState::startMenu:
		switch (e.keysym.sym)
		{
		case SDLK_i:
			PrintInfo();
			break;
		default:
		{
			m_State = GameState::playing;

			SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::basementTrack) };
			track->SetVolume(15);
			track->Play(true);
			break;
		}

		}
		break;
	case Game::GameState::death:
		switch (e.keysym.sym)
		{
		case SDLK_i:
			PrintInfo();
			break;
		default:
		{

			SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::deathScreen) };
			track->Stop();
			Cleanup();
			Initialize();
			m_State = GameState::startMenu;
			break;
		}

		}
		break;
	case Game::GameState::victory:
		switch (e.keysym.sym)
		{
		case SDLK_i:
			PrintInfo();
			break;
		default:
		{

			SoundStream* track{ m_pSoundEffectManager->GetMusicTrackEffect(SoundEffectManager::MusicTrackLookup::victoryScreen) };
			track->Stop();
			Cleanup();
			Initialize();
			m_State = GameState::startMenu;
			break;
		}

		}
		break;
	case Game::GameState::playing:
		m_pPlayer->ProcessKeyUpEvent(e);
		break;
	}

}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::InitPlayer(IsaacHealthBar* isaacHealthBar)
{
	m_pPlayer = new Isaac(m_TextureManager, m_pSoundEffectManager, isaacHealthBar,
		Point2f{ m_Window.width / 2.0f,  m_Window.height / 2.0f });
}

void Game::DrawPlayer() const
{
	m_pPlayer->Draw();
}

void Game::UpdatePlayer(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec, m_pTearManager, m_TextureManager, m_pFloor->GetCurrentRoom(), m_pItemManager);
}

void Game::DeletePlayer()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Game::InitTearManager()
{
	m_pTearManager = new TearManager{ };
}

void Game::UpdateTearManager(float elapsedSec)
{
	m_pTearManager->UpdateTears(elapsedSec, m_pFloor->GetCurrentRoom(), m_pPlayer);
}

void Game::DeleteTearManager()
{
	delete m_pTearManager;
	m_pTearManager = nullptr;
}

void Game::InitUIManager(IsaacHealthBar* isaacHealthBar)
{

	Minimap* pMinimap{ new Minimap{m_TextureManager,m_pFloor->GetLayout(), m_pFloor->GetCurrentIndexes(), m_pFloor->GetMaxRows(), m_pFloor->GetMaxCols()} };

	m_pUIManager = new UIManager(isaacHealthBar, pMinimap);
	pMinimap = nullptr;
}

void Game::DrawUIManager() const
{
	m_pUIManager->Draw(m_Camera.GetCameraView(m_pPlayer->GetCenter()));
}

void Game::DeleteUIManager()
{
	delete m_pUIManager;
}

void Game::InitFloor(RoomManager* roomManager)
{
	m_pFloor = new Floor{};
	m_pFloor->GenerateFloor(roomManager, m_TextureManager, m_pItemManager);
	m_pFloor->ActivateDoors();
	m_pFloor->InitEnemies(m_pEnemyManager);
}

void Game::DrawFloor() const
{
	m_pFloor->Draw();
}

void Game::DeleteFloor()
{
	delete m_pFloor;
}

void Game::PrintInfo()
{
	std::cout << "--------------------Tutorial--------------------\n";

	std::cout << "WASD for movement\n";
	std::cout << "Arrow keys to shoot\n";

	std::cout << "--------------------Tutorial--------------------\n";
}
