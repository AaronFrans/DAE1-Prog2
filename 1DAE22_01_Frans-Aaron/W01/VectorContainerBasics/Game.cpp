#include "pch.h"
#include "Game.h"
#include "Card.h"
#include <iostream>

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	InitCards();
}

void Game::Cleanup( )
{
	DeleteCard();
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawCards();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_KP_PLUS:
		//std::cout << "Left arrow key released\n";
		//AddIntToVector(m_Numbers1);
		IncrementVectorMembers(m_Numbers2);
		break;
	case SDLK_KP_MINUS:
		//std::cout << "`Right arrow key released\n";
		//RemoveLastFromVector(m_Numbers1);
		DecrementVectorMembers(m_Numbers2);
		break;
	case SDLK_s:
		//std::cout << "`Right arrow key released\n";
		//RemoveLastFromVector(m_Numbers1);
		ShuffleCards();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
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

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
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

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::AddIntToVector(std::vector<int>& v)
{
	v.push_back(rand() % 30);
	PrintVector(v);
}

void Game::RemoveLastFromVector(std::vector<int>& v)
{
	if (v.size() > 0)
	{
		v.pop_back();
		
	}
	PrintVector(v);

}

void Game::IncrementVectorMembers(std::vector<int>& v)
{

	for (int i = 0; i < v.size(); i++)
	{
		v[i]++;
	}
	PrintVector(v);

}

void Game::DecrementVectorMembers(std::vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i]--;
	}
	PrintVector(v);
}

void Game::PrintVector(std::vector<int>& v)
{
	std::cout <<  "Vector: ";
	for (int number : v)
	{
		std::cout << number << ", ";
	}
	std::cout << "\n";

}

void Game::InitCards()
{

	for (int i = 1; i < (int)Card::Suit::count; i++)
	{
		for (int j = Card::m_MinRank; j <= Card::m_MaxRank; j++)
		{
			
			m_Cards.push_back(new Card{ 
				(Card::Suit)i,
				j 
				});
		}

	}

}

void Game::DrawCards() const
{
	float cardHeight = m_Cards[0]->GetHeight() * 0.5f;
	float cardWidth = m_Cards[0]->GetWidth() * 0.5f;

	for (int i = 0; i < (int)Card::Suit::count - 1; i++)
	{
		for (int j = 0; j <= Card::m_MaxRank - 1; j++)
		{
			m_Cards[j + ((Card::m_MaxRank)*i)]->Draw(
				Rectf{
					0 + (cardWidth * j) / 2,
					0 + cardHeight * i,
					cardWidth,
					cardHeight
				}
			);
		}

	}



}


void Game::DeleteCard()
{
	for (Card* card: m_Cards)
	{
		delete card;
		card = nullptr;
	}
}
void Game::ShuffleCards()
{
	for (int i = 0; i < 100; i++)
	{
		int i1 = rand() % (m_Cards.size() - 1);
		int i2 = rand() % (m_Cards.size() - 1);

		Card* temp = m_Cards[i1];
		m_Cards[i1] = m_Cards[i2];
		m_Cards[i2] = temp;

		temp = nullptr;


	}

}

