#include "pch.h"
#include "PickUpManager.h"
#include "pickUp.h"
#include "utils.h"
#include "Room.h"

PickUpManager::PickUpManager()
{
}

void PickUpManager::DrawPickups(Room* currentRoom) const
{
	for (std::pair<Room*, std::vector<PickUp*>> roomWithPickUps : m_pPickupsPerRoom)
	{
		if (currentRoom == roomWithPickUps.first)
		{
			for (PickUp* pickUp : roomWithPickUps.second)
			{
				pickUp->Draw();
			}
		}

	}
}

void PickUpManager::Update(Room* currentRoom, Isaac* isaac)
{
	for (int i = 0; i < m_pPickupsPerRoom[currentRoom].size(); i++)
	{
		if (m_pPickupsPerRoom[currentRoom][i]->HasIsaacCollision(isaac))
		{
			PickUp* temp{ m_pPickupsPerRoom[currentRoom][i] };
			m_pPickupsPerRoom[currentRoom][i] =
				m_pPickupsPerRoom[currentRoom][m_pPickupsPerRoom[currentRoom].size() - 1];
			m_pPickupsPerRoom[currentRoom][m_pPickupsPerRoom[currentRoom].size() - 1] =
				temp;
			delete temp;
			m_pPickupsPerRoom[currentRoom].pop_back();

			break;
		}
	}
}



void PickUpManager::AddPickUp(Room* currentRoom, const TextureManager& textureManager)
{
	PickUp::Type randomType((PickUp::Type)utils::GetRand((int)PickUp::Type::fullHeart, (int)PickUp::Type::halfHeart));
	Point2f center{ currentRoom->GetFreeSpot() };


	switch (randomType)
	{
	case PickUp::Type::fullHeart:
		m_pPickupsPerRoom[currentRoom].push_back(new PickUp{ 
			textureManager.GetTexture(TextureManager::TextureLookup::pickupFullHeart),
			randomType,
			center
			});
		break;
	case PickUp::Type::halfHeart:
		m_pPickupsPerRoom[currentRoom].push_back(new PickUp{ 
			textureManager.GetTexture(TextureManager::TextureLookup::pickupHalfHeart),
			randomType,
			center
			});
		break;
	default:
		break;
	}


}

bool PickUpManager::RoomHasPickUps(Room* currentRoom)
{
	return m_pPickupsPerRoom[currentRoom].size() != 0;
}

