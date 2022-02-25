#include "pch.h"
#include "Game.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include "utils.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
	, m_MousePos{}
	, m_Destroyer{ 0.0f,0.0f,20.0f,20.0f }
	, m_PowerUpRadius{}
	, m_Rows{ 3 }
	, m_Cols{ 4 }
	, m_MaxNrItems{ m_Rows * m_Cols }
	, m_pTestedManager{ nullptr }
	, m_TestedManagerSize{ 0 }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	// Get radius of a power up
	Texture text{ "./Resources/Images/PowerUp.png" };
	m_PowerUpRadius = text.GetWidth() / 2;

	// TODO: 1. Uncomment next call of TestWithoutDrawing
	// It tests the constructor, AddItem, Size and destructor 
	TestWithoutDrawing( );

	// TODO: 2. Uncomment next call of InitTestWithDrawing
	InitTestWithDrawing( );
}

void Game::Cleanup( )
{
	delete m_pTestedManager;
	m_pTestedManager = nullptr;
}

void Game::Update( float elapsedSec )
{
	MoveDestroyer( m_MousePos );
	if ( m_pTestedManager != nullptr )
	{
		m_pTestedManager->Update( elapsedSec );
		TestHittingCircle( m_Centers, m_Destroyer );
		TestHittingItem( m_pTestedManager, m_Destroyer );
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawDestroyer( );
	if ( m_pTestedManager != nullptr )
	{
		m_pTestedManager->Draw( );
		DrawCircles( m_Centers, m_Types );
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePos.x = float( e.x );
	m_MousePos.y = float( e.y );
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::ShowTestMessage( ) const
{
	std::cout << "Test of Draw, Update and HitItem :\n";
	std::cout << "1. Verify that the colored circles coincide with the drawn PowerUp objects.\n";
	std::cout << "2. Verify that the PowerUp objects disappear when the mouse's red rectangle hits it.\n";
	std::cout << "3. Verify that the number of drawn PowerUp objects is equal to the displayed number.\n";
	std::cout << "4. Verify that the game stops without memory leaks, even when still some items weren't hit.\n";
	ShowNrItems( );
}

void Game::ShowNrItems( ) const
{
	std::cout << "Number of PowerUp objects " << m_TestedManagerSize << "\n";
}

void Game::TestWithoutDrawing( )
{
	// Data that holds info about the added items
	std::cout << "--> Test without drawing <--\n";
	std::vector<Point2f> centers;
	std::vector<PowerUp::Type> types;
	size_t size{ 0 };

	// Create the manager
	std::cout << "--> Create PowerUpManager and verify Size() result <--\n";
	PowerUpManager * pManager{ new PowerUpManager( ) };
	TestSize( pManager, size );

	// Verify that adding items works correctly
	const int maxNr{ 20 };
	std::cout << "--> Call AddItem " << maxNr << " times and verify Size() result <--\n";
	Point2f center{};
	float dx{ m_PowerUpRadius * 2 };
	float dy{ m_PowerUpRadius * 2 };
	for ( int nr = 0; nr < maxNr; ++nr )
	{
		center.x += dx;
		center.y += dy;
		centers.push_back( center );
		types.push_back(rand( ) % 2 == 0 ? PowerUp::Type::brown : PowerUp::Type::green);
	}
	TestAddingItems( pManager, centers, types );
	size += centers.size();


	// Verify that hitting items works correctly
	// Shuffle the centers and then hit one after the other
	std::cout << "--> Call HitItem " << maxNr << " times and verify Size() result <--\n";
	for (size_t i = 0; i < 100; i++)
	{
		size_t index1{ rand() % centers.size() };
		size_t index2{ rand() % centers.size() };
		Point2f temp{ centers[index1] };
		centers[index1] = centers[index2];
		centers[index2] = temp;
	}
	TestHittingItems( pManager, centers );
	size = 0;

	// Add again items
	std::cout << "--> Again call AddItem several times and verify Size() result <--\n";
	TestAddingItems( pManager, centers, types );
	size += centers.size();

	// Verify destructor
	std::cout << "--> Call destructor <--\n";
	delete pManager;
	pManager = nullptr;
}

void Game::InitTestWithDrawing( )
{
	std::cout << "\n--> Init tests with drawing <--\n";
	m_pTestedManager = new PowerUpManager( );
	float dx{ m_Window.width / m_Cols };
	float dy{ m_Window.height / m_Rows };
	Point2f center{ dx / 2, dy / 2 };
	for ( size_t row{ 0 }; row < m_Rows; ++row )
	{
		for ( size_t col{ 0 }; col < m_Cols; ++col )
		{
			m_Centers.push_back( center );
			m_Types.push_back( rand( ) % 2 == 0 ? PowerUp::Type::brown : PowerUp::Type::green );

			// next column
			center.x += dx;
		}
		// next row
		center.y += dy;
		center.x = dx / 2;
	}
	TestAddingItems( m_pTestedManager, m_Centers, m_Types );
	m_TestedManagerSize += m_MaxNrItems;
	ShowTestMessage( );
}

void Game::TestSize( PowerUpManager* pTestedManager, size_t expectedSize )
{
	assert( pTestedManager->Size( ) == expectedSize );
}

void Game::TestAddingItems( PowerUpManager* pManager, const std::vector<Point2f>& centers, const std::vector< PowerUp::Type >& types )
{
	size_t size{ pManager->Size( ) };
	for ( size_t idx{0}; idx < centers.size(); ++idx )
	{
		PowerUp* pAddedItem = pManager->AddItem( centers[idx], types[idx] );
		assert(pAddedItem != nullptr);
		++size;
		TestSize( pManager, size );
	}
}


void Game::TestHittingItems( PowerUpManager* pTestedManager, const std::vector<Point2f>& centers )
{
	// Hit all the items
	Rectf destroyer{ 0,0,m_PowerUpRadius / 2,m_PowerUpRadius / 2 };

	for ( Point2f center : centers )
	{
		// Make destroyer hit the item
		destroyer.left = center.x - destroyer.width / 2;
		destroyer.bottom = center.y - destroyer.height / 2;
		 
		// Test HitItem
		size_t size{ pTestedManager->Size( ) };
		assert( pTestedManager->HitItem( destroyer ) == true );
		--size;
		TestSize( pTestedManager, size );
	}
}

void Game::TestHittingItem( PowerUpManager* pTestedManager, const Rectf& destroyer )
{
	size_t size{ pTestedManager->Size( ) };
	if ( pTestedManager->HitItem( destroyer ) == true )
	{
		--size;
		ShowNrItems( );
	}
	TestSize( pTestedManager, size );
}

void Game::TestHittingCircle(  std::vector<Point2f>& centers, const Rectf& destroyer )
{
	for ( Point2f& center : centers )
	{
		Circlef powerUp{ center, m_PowerUpRadius };
		if ( utils::IsOverlapping( destroyer, powerUp ) )
		{
			center.x = -center.x;
			center.y = -center.y;
			m_TestedManagerSize--;
		}
	}
}


void Game::MoveDestroyer( const Point2f& newCenter )
{
	m_Destroyer.left = newCenter.x - m_Destroyer.width / 2;
	m_Destroyer.bottom = newCenter.y - m_Destroyer.height / 2;
}

void Game::DrawDestroyer( ) const
{
	utils::SetColor(Color4f { 1.0f,0.0f,0.0f,1.0f } );
	utils::FillRect( m_Destroyer );
}

void Game::DrawCircles( const std::vector<Point2f>& centers, const std::vector< PowerUp::Type >& types ) const
{
	for ( size_t idx{ 0 }; idx < centers.size( ) ; ++idx )
	{
			if ( m_Types[idx] == PowerUp::Type::brown )
			{
				utils::SetColor(Color4f{ 1.0f,0.5f,0.2f,0.5f } );
			}
			else
			{
				utils::SetColor(Color4f{ 0.5f,1.0f,0.5f,0.5f } );
			}
			utils::FillEllipse( m_Centers[idx], m_PowerUpRadius, m_PowerUpRadius);
	}
}
