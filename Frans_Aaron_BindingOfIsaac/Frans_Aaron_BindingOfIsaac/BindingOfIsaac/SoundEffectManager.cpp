#include "pch.h"
#include "SoundEffectManager.h"
#include "SoundEffect.h"
#include "SoundStream.h"

SoundEffectManager::SoundEffectManager()
{
	InitSoundEffects();

	InitMusicTracks();
}

SoundEffectManager::~SoundEffectManager()
{
	for (SoundEffect* effect : m_pSoundEffects)
	{
		delete effect;
	}
	for (SoundStream* track: m_pMusicTracks)
	{
		delete track;
	}
}

SoundEffect* SoundEffectManager::GetSoundEffect(SoundEffectLookup effectName)
{
	if ((int)effectName > m_pSoundEffects.size() - 1)
	{
		return nullptr;
	}

	return m_pSoundEffects[(int)effectName];
}

SoundStream* SoundEffectManager::GetMusicTrackEffect(MusicTrackLookup trackName)
{
	if ((int)trackName > m_pMusicTracks.size() - 1)
	{
		return nullptr;
	}

	return m_pMusicTracks[(int)trackName];
}

void SoundEffectManager::InitSoundEffects()
{
	InitIsaacSoundEffects();
	InitTearSoundEffects();
	InitGameObjectSoundEffects();
	InitRoomSoundEffects();
	InitEnemySoundEffects();
	InitBossSoundEffects();
	InitOtherSoundEffects();
}

void SoundEffectManager::InitIsaacSoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Isaac/Hurt-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Isaac/Hurt-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Isaac/Hurt-3.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Isaac/Isaac-Dies.wav"));
}

void SoundEffectManager::InitTearSoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Tears/Tear-Destroyed.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Tears/Tear-Shot-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Tears/Tear-Shot-2.wav"));
}

void SoundEffectManager::InitGameObjectSoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/GameObjects/Poop-Destroyed.wav"));
}

void SoundEffectManager::InitRoomSoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Rooms/Doors-Close.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Rooms/Doors-Open.wav"));
}

void SoundEffectManager::InitEnemySoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Enemies/Animal-Death-Sound-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Enemies/Animal-Death-Sound-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Enemies/Animal-Death-Sound-3.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Enemies/Fly-Moving.wav"));
}

void SoundEffectManager::InitBossSoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Death-Splatter-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Death-Splatter-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Death-Splatter-3.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Attack-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Attack-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Attack-3.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Roar-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Roar-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Roar-3.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Jump-Roar-4.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Spit-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Spit-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Spit-3.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Splatter-1.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Splatter-2.wav"));
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Boss/Monstro/Splatter-3.wav"));
}

void SoundEffectManager::InitOtherSoundEffects()
{
	m_pSoundEffects.push_back(new SoundEffect("Resources/Music/Sound-Effects/Other/Game-Over-Screen.ogg"));
}

void SoundEffectManager::InitMusicTracks()
{
	m_pMusicTracks.push_back(new SoundStream("Resources/Music/Music-Tracks/Basement-Track.ogg"));
	m_pMusicTracks.push_back(new SoundStream("Resources/Music/Music-Tracks/Boss-Fight.ogg"));
	m_pMusicTracks.push_back(new SoundStream("Resources/Music/Music-Tracks/Title-Screen.ogg"));
}
