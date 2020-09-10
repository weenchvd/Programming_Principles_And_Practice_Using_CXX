/* Exercise 18.12 */

/*
	Order of actions:
		1) hunter's (your) turn
		2) Wumpus's turn
*/

using namespace std;

namespace WumpusGame {
	// can be changed
	constexpr int sizeOfCave = 1;								// range [0:19], default == 1
	constexpr int numberOfArrows = 5;

	// don't change
	constexpr int numberOfRooms = sizeOfCave * 10 + 10;
	constexpr int numberOfTunnels = 3;
	constexpr int numberOfPaths = numberOfRooms * numberOfTunnels;
	constexpr int firstRoom = 0;
	constexpr int lastRoom = numberOfRooms - 1;
	constexpr int notAssigned = firstRoom - 1;

	const char* space_c2 = "  ";
	const char* space_c4 = "    ";
	const char* space_c6 = "      ";
	const char* space_c8 = "        ";
	const char* inRoom_c10 = " in room #";
	const char* room_c6 = "Room #";
	const char* colon_c2 = ": ";
	const char* tunnel_c10 = "tunnel -> ";
	const char* gameOver_c9 = "Game over";
	const char* line_c60 = "------------------------------------------------------------";
	const char* help =
		"\nWelcome to the game \"Hunt the Wumpus!\"\n"
		"Example of action:\n"
		"'m13' - go to room #13\n"
		"'s3' - shoot at room #3, 's16-7' - shoot at room #16-7, 's1-4-2' - shoot at room #1-4-2\n\n";

	enum class ActionType {
		NOACTION, MOVE, SHOOT,
		PRINTMAP
	};

	enum class State {
		INITIALSTATE				= static_cast<int>(0x0000),
		WUMPUSISMOVING				= static_cast<int>(0x0001),
		YOUCAMETOWUMPUS				= static_cast<int>(0x0002),
		WUMPUSCAMETOYOU				= static_cast<int>(0x0004),
		BATCARRIEDYOUTOWUMPUS		= static_cast<int>(0x0008),
		YOUKILLEDWUMPUS				= static_cast<int>(0x0010),
		YOUKILLEDYOURSELF			= static_cast<int>(0x0020)
	};

	struct Action {
		Action() : type{ ActionType::NOACTION }, room1{ notAssigned }, room2{ notAssigned }, room3{ notAssigned } {}
		ActionType type;
		int room1;												// room for the move or shoot
		int room2;												// room for the shoot
		int room3;												// room for the shoot
	};

	struct Room {
		Room() : adj1{ notAssigned }, adj2{ notAssigned }, adj3{ notAssigned } {}
		int adj1;												// number of the adjoining room #1
		int adj2;												// number of the adjoining room #2
		int adj3;												// number of the adjoining room #3
	};

	class Cave {
	public:
		Cave();
		void PrintPrompt() const;
		void GetAction();
		bool DoAction();
	private:
		const int nRooms{ numberOfRooms };						// number of rooms
		int hRoom;												// room number with hunter (you)
		int wRoom;												// room number with Wumpus
		int pRoom;												// room number with the pit
		int bRoom;												// room number with the bat
		int nArrows{ numberOfArrows };							// number of arrows
		int state{ int(State::INITIALSTATE) };
		Room rooms[numberOfRooms];
		Action act;

		void ChangeRandomSeed() const;
		void BuildTunnels();
		inline int NextRoom(int first, int last, int n) const;
		void ErasePaths();
		void Move();
		void Shoot();
		bool BatAction();
		bool Check();
		void PrintMap() const;
		int GetRandomNextRoom(int prevRoom, int currentRoom) const;
		bool IsValidNextRoom(int currentRoom, int nextRoom) const;
		bool ParseInput(const string& s, Action& a) const;
	};

	void PlayHuntTheWumpus();
}

void ClearInput(istream& is);
