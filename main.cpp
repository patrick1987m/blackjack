#include "/HeaderFiles/programTools.h"
#include "/EarlyGameDevelopment/TextBasedBlackJack/Includes/Random.h"
/*
A Text based BlackJack Game:



*/

struct Card
{
	enum Rank
	{
		rank_ace,
		rank_2,
		rank_3,
		rank_4,
		rank_5,
		rank_6,
		rank_7,
		rank_8,
		rank_9,
		rank_10,
		rank_jack,
		rank_queen,
		rank_king,

		max_ranks
	};

	enum Suit
	{
		suit_club,
		suit_diamond,
		suit_heart,
		suit_spade,

		max_suits
	};

	static constexpr std::array allRanks{ rank_ace, rank_2, rank_3, rank_4, rank_5,rank_6, rank_7, rank_8,
	rank_9, rank_10, rank_jack,rank_queen, rank_king };
	static constexpr std::array allSuits{ suit_club, suit_diamond, suit_heart, suit_spade };

	Rank rank{ };
	Suit suit{ };

	friend std::ostream& operator<<(std::ostream& out, const Card& card)
	{
		static constexpr std::array ranks{ 'A', '2', '3', '4', '5', '6', '7',
			'8', '9', 'T', 'J', 'Q', 'K' };
		static constexpr std::array suits{ 'C', 'D', 'H', 'S' };
		out << ranks[card.rank] << suits[card.suit];
		return out;
	}
	int value() const
	{
		static constexpr std::array rankValues{ 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
		return rankValues[rank];
	}
};
class Deck
{
public:
	Deck()
	{
		std::size_t count{ 0 };
		for (auto suit : Card::allSuits)
		{
			for (auto rank : Card::allRanks)
			{
				m_cards[count++] = Card{ rank, suit };
			}
		}
	}
	void shuffle()
	{
		std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
		m_nextCardIndex = 0;
	}

	Card dealCard()
	{
		assert(m_nextCardIndex != 52 && "Deck::dealCard has ran out of cards!");
		return m_cards[m_nextCardIndex++];
	}

private:
	std::array<Card, 52> m_cards{ };
	std::size_t m_nextCardIndex{ 0 };
};
class Player
{
public:
	// We will use a function to add the card to the player's score, since we now need to count aces
	void addToScore(Card card)
	{
		m_score += card.value();

		if (card.rank == Card::rank_ace)
		{
			++m_aceCount;
		}
	}

	void consumeAces(int maxScore)
	{
		while (m_score > maxScore && m_aceCount > 0)
		{
			m_score -= 10;
			--m_aceCount;
		}
	}
	int score() { return m_score; }

private:
	int m_score{ 0 };
	int m_aceCount{ 0 };
};
namespace Settings
{
	// Maximum score before losing.
	constexpr int bust{ 21 };

	// Minimum score that the dealer has to have
	constexpr int dealerStopsAt{ 17 };
}

// Function to determine if player wants a hit
bool playerWantsHit()
{
	while (true)
	{
		std::cout << "(h) to hit, or (s), to stand: ";

		char ch{ };
		std::cin >> ch;

		switch (ch)
		{
		case 'h':
		case 'H':
			return true;
		case 's':
		case 'S':
			return false;
		}
	}
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck& deck, Player& player)
{
	while (player.score() < Settings::bust && playerWantsHit())
	{
		Card card{ deck.dealCard() };
		player.addToScore(card);
		player.consumeAces(Settings::bust);

		std::cout << "You were dealt " << card << ". You now have: " <<
			player.score() << '\n';
	}

	if (player.score() > Settings::bust)
	{
		std::cout << "You went bust!\n";
		return true;
	}
	return false;
}
// Returns true if the dealer went bust. False Otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
	while (dealer.score() < Settings::dealerStopsAt)
	{
		Card card{ deck.dealCard() };
		dealer.addToScore(card);
		dealer.consumeAces(Settings::bust);

		std::cout << "The dealer flips a " << card << ". They now have: " << dealer.score() << '\n';
	}
	if (dealer.score() > Settings::bust)
	{
		std::cout << "The dealer went bust!\n";
		return true;
	}

	return false;
}
enum class GameResult
{
	playerWon,
	dealerWon,
	tie
};
GameResult playBlackJack()
{
	Deck deck{ };
	deck.shuffle();

	Player dealer{ };
	Card card1{ deck.dealCard() };
	dealer.addToScore(card1);
	std::cout << "The dealer is showing " << card1 << "(" << dealer.score() << ")\n";

	Player player{ };
	Card card2{ deck.dealCard() };
	Card card3{ deck.dealCard() };

	player.addToScore(card2);
	player.addToScore(card3);
	std::cout << "You are showing " << card2 << ' ' << card3 << " (" << player.score() << ")\n";

	if (playerTurn(deck, player))	// If the player busted
	{
		return GameResult::dealerWon;
	}
	if (dealerTurn(deck, dealer))
	{
		return GameResult::playerWon;
	}
	if (player.score() == dealer.score())
	{
		return GameResult::tie;
	}
	return (player.score() > dealer.score() ? GameResult::playerWon : GameResult::dealerWon);
}
void gamePlay()
{
	switch (playBlackJack())
	{
	case GameResult::playerWon:
		std::cout << "You win!\n";
		break;
	case GameResult::dealerWon:
		std::cout << "You lost!\n";
		break;
	case GameResult::tie:
		std::cout << "It's a tie.\n";
		break;
	default:
		std::cout << "Invalid!\n";
		break;
	}
}

// Text function for introducing the game:
void introText()
{
	std::cout << "Welcome to a text based version of Blackjack: \n";
}



// Testing Code
void testingCode()
{
	introText();

	gamePlay();
	// Ask the user if they want to play again!
	while (true)
	{
		std::cout << "Would you like to play again? (Y/y for Yes and (N/n) to exit the game) \n";
		char ch{ };
		std::cin >> ch;

		// Handle Invalid input
		if (!std::cin)
		{
			// Fix and clear the issue
			std::cin.clear();
			std::cout << "That was an Invalid input! \n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		switch (ch)
		{
		case 'y':
		case 'Y':
			gamePlay();
			continue;
			break;
		case 'n':
		case 'N':
			std::cout << "Thank you for playing!\n";
			return;
			break;
		default:
			std::cout << "That is not valid input!\n";
			break;
		}
	}
}
int main()
{
	testingCode();

	programTools::pauseConsole();

	return 0;
}