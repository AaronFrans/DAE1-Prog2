#pragma once
#include <vector>

class SoundEffect;
class SoundStream;

class SoundEffectManager final
{

public:

	enum class SoundEffectLookup
	{
		//Isaac
		hurt1,
		hurt2,
		hurt3,
		isaacDies,
		//Tears
		tearDestroyed,
		tearShot1,
		tearShot2,
		//GameObjects
		poopDestroyed,
		//Rooms
		doorClose,
		doorOpen,
		//Enemies
		animalDeathSound1,
		animalDeathSound2,
		animalDeathSound3,
		flyMoving,
		//Bosses
		deathSplatter1,
		deathSplatter2,
		deathSplatter3,
		jumpAttack1,
		jumpAttack2,
		jumpAttack3,
		jumpRoar1,
		jumpRoar2,
		jumpRoar3,
		jumpRoar4,
		spit1,
		spit2,
		spit3,
		splatter1,
		splatter2,
		splatter3,
		//Other
		gameOverScreen,

	};

	enum class MusicTrackLookup
	{
		basementTrack,
		bossFight,
		titleScreen,
		deathScreen,
		victoryScreen,
	};

	SoundEffectManager();

	SoundEffectManager(const SoundEffectManager& rhs) = default;
	SoundEffectManager(SoundEffectManager && rhs) = default;
	SoundEffectManager& operator=(const SoundEffectManager & rhs) = default;
	SoundEffectManager& operator=(SoundEffectManager && rhs) = default;
	~SoundEffectManager();

	
	SoundEffect* GetSoundEffect(SoundEffectLookup effectName);

	SoundStream* GetMusicTrackEffect(MusicTrackLookup trackName);

private:

	std::vector<SoundEffect*> m_pSoundEffects;
	std::vector<SoundStream*> m_pMusicTracks;

	void InitSoundEffects();
	void InitIsaacSoundEffects();
	void InitTearSoundEffects();
	void InitGameObjectSoundEffects();
	void InitRoomSoundEffects();
	void InitEnemySoundEffects();
	void InitBossSoundEffects();
	void InitOtherSoundEffects();


	void InitMusicTracks();

};

