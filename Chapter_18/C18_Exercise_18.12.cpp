/* Exercise 18.12 */

#include<iostream>
#include<istream>
#include<string>
#include<vector>
#include<iomanip>
#include<sstream>
#include"C18_Exercise_18.12.h"

using namespace std;
using namespace WumpusGame;

inline void error(string s) { throw runtime_error(s); }
inline void error(const string& s, const string& s2) { error(s + s2); }
inline void error(const string& s, int i) { ostringstream os; os << s << ": " << i; error(os.str()); }
inline void keep_window_open() { char ch; cin >> ch; }
inline int randint(int max) { return rand() % max; }
inline int randint(int min, int max) { return randint(max - min) + min; }

int main()
{
	enum Action {
		EXIT = -1, PRINTACTIONLIST,
		HUNT
	};
	const string actionList = "\tList of actions:\n"
	"  (1) Hunt the Wumpus\n"
	"  (-1) Exit, (0) Print the list of actions\n";
	cout << actionList;
	int action;
	bool cond{ true };
	while (cond) try {
		cout << "\nPlease enter the action: ";
		if (!(cin >> action)) { ClearInput(cin); error("Error. Incorrect input"); }
		char ch;
		cin.get(ch);
		switch (action) {
		case HUNT: {
			PlayHuntTheWumpus();
			break;
		}
		case PRINTACTIONLIST:
			cout << actionList;
			break;
		case EXIT:
			cond = false;
			break;
		default:
			error("Error. Incorrect action number");
			break;
		}
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Error. Exception\n";
		return 1;
	}
	return 0;
}

void WumpusGame::PlayHuntTheWumpus()
{
	Cave cave;
	cout << help << endl
		<< space_c2 << "You have " << numberOfArrows << " arrows" << endl
		<< space_c2 << "Wumpus is asleep" << endl;
	bool toPlay{ true };
	while (toPlay) {
		cave.PrintPrompt();
		cave.GetAction();
		toPlay = cave.DoAction();
	}
}

Cave::Cave()
{
	ChangeRandomSeed();
	BuildTunnels();
	hRoom = randint(firstRoom, lastRoom + 1);
	while (true) {
		wRoom = randint(firstRoom, lastRoom + 1);
		if (wRoom == hRoom) continue;
		break;
	}
	while (true) {
		pRoom = randint(firstRoom, lastRoom + 1);
		if (pRoom == hRoom || pRoom == wRoom) continue;
		break;
	}
	while (true) {
		bRoom = randint(firstRoom, lastRoom + 1);
		if (bRoom == hRoom || bRoom == wRoom || bRoom == pRoom) continue;
		break;
	}
}

void Cave::PrintPrompt() const
{
	cout << endl << space_c2 << "You are in room #" << hRoom << endl;
	if (rooms[ref[hRoom]].adj1 == ref[wRoom] || rooms[ref[hRoom]].adj2 == ref[wRoom]
		|| rooms[ref[hRoom]].adj3 == ref[wRoom]) {
		cout << space_c4 << "I smell the wumpus" << endl;
	}
	if (rooms[ref[hRoom]].adj1 == ref[pRoom] || rooms[ref[hRoom]].adj2 == ref[pRoom]
		|| rooms[ref[hRoom]].adj3 == ref[pRoom]) {
		cout << space_c4 << "I feel a breeze" << endl;
	}
	if (rooms[ref[hRoom]].adj1 == ref[bRoom] || rooms[ref[hRoom]].adj2 == ref[bRoom]
		|| rooms[ref[hRoom]].adj3 == ref[bRoom]) {
		cout << space_c4 << "I hear a bat" << endl;
	}
	int adj1 = rooms[ref[hRoom]].adj1;
	int adj2 = rooms[ref[hRoom]].adj2;
	int adj3 = rooms[ref[hRoom]].adj3;
	cout << space_c2 << "Tunnels lead to " << rooms[adj1].num << ", "
		<< rooms[adj2].num << ", " << rooms[adj3].num << endl;
}

void Cave::GetAction()
{
	const char* unknownAction = "Unknown action. Please try again";
	string input;
	while (true) {
		cout << space_c2 << "Enter an action: ";
		getline(cin, input);
		if (!cin) {
			cout << space_c4 << unknownAction << endl;
			continue;
		}
		for (int i = 0; i < input.size(); i++) input[i] = tolower(input[i]);
		if (ParseInput(input, act)) break;
		cout << space_c4 << unknownAction << endl;
	}
}

bool Cave::DoAction()
{
	switch (act.type) {
	case ActionType::MOVE:
		Move();
		break;
	case ActionType::SHOOT:
		if (nArrows > 0) Shoot();
		else {
			cout << space_c4 << "You have no arrows" << endl;
			return true;
		}
		break;
	case ActionType::PRINTMAP:
		PrintMap();
		return true;
		break;
	default:
		cout << "Error. Unknown action" << endl;
		break;
	}
	if (state & int(State::WUMPUSISMOVING)) {
		int old = wRoom;
		while (true) {
			wRoom = randint(firstRoom, lastRoom + 1);
			if (ref[wRoom] == rooms[ref[old]].adj1 || ref[wRoom] == rooms[ref[old]].adj2
				|| ref[wRoom] == rooms[ref[old]].adj3) break;
			continue;
		}
		if (wRoom == hRoom) state |= int(State::WUMPUSCAMETOYOU);
	}
	return Check();
}

void Cave::Move()
{
	cout << space_c4 << "You go to room #" << act.room1 << endl;
	hRoom = act.room1;
	if (hRoom == wRoom) state |= int(State::YOUCAMETOWUMPUS);
}

void Cave::Shoot()
{
	cout << space_c4 << "You shoot at rooms #" << act.room1 << "-" << act.room2 << "-" << act.room3 << endl;
	if (!(state & int(State::WUMPUSISMOVING))) cout << space_c4 << "Wumpus is awake" << endl;
	state |= int(State::WUMPUSISMOVING);
	if (act.room1 == wRoom || act.room2 == wRoom || act.room3 == wRoom) state |= int(State::YOUKILLEDWUMPUS);
	if (act.room1 == hRoom || act.room2 == hRoom || act.room3 == hRoom) state |= int(State::YOUKILLEDYOURSELF);
	nArrows--;
	cout << space_c4 << "You have " << nArrows << " arrows left" << endl;
}

bool Cave::BatAction()
{
	int n = randint(firstRoom, lastRoom + 1);
	while (hRoom == n) n = randint(firstRoom, lastRoom + 1);
	hRoom = n;
	if (hRoom == wRoom) state |= int(State::BATCARRIEDYOUTOWUMPUS);
	cout << space_c4 << "You are in a room with a bat. She grabs you and carries you to room #" << hRoom << endl;
	while (hRoom == n || bRoom == n) n = randint(firstRoom, lastRoom + 1);
	bRoom = n;
	return Check();
}

bool Cave::Check()
{
	if (state & int(State::YOUKILLEDWUMPUS)) {
		cout << space_c6 << "You killed Wumpus!" << endl << space_c8 << gameOver_c9 << endl;
		return false;
	}
	if (state & int(State::YOUKILLEDYOURSELF)) {
		cout << space_c6 << "You killed yourself!" << endl << space_c8 << gameOver_c9 << endl;
		return false;
	}
	if (state & int(State::YOUCAMETOWUMPUS)) {
		cout << space_c6 << "You came to Wumpus's room..." << endl;
		cout << space_c6 << "You were eaten by the Wumpus!" << endl << space_c8 << gameOver_c9 << endl;
		return false;
	}
	if (state & int(State::WUMPUSCAMETOYOU)) {
		cout << space_c6 << "Wumpus came to your room..." << endl;
		cout << space_c6 << "You were eaten by the Wumpus!" << endl << space_c8 << gameOver_c9 << endl;
		return false;
	}
	if (state & int(State::BATCARRIEDYOUTOWUMPUS)) {
		cout << space_c6 << "Bat carried you to Wumpus's room..." << endl;
		cout << space_c6 << "You were eaten by the Wumpus!" << endl << space_c8 << gameOver_c9 << endl;
		return false;
	}
	if (hRoom == pRoom) {
		cout << space_c6 << "You fell into a bottomless pit..." << endl << space_c8 << gameOver_c9 << endl;
		return false;
	}
	if (hRoom == bRoom) return BatAction();
	return true;
}

void Cave::ChangeRandomSeed() const
{
	time_t raw;
	time(&raw);
	tm t = *localtime(&raw);
	int seed = t.tm_sec + t.tm_min + t.tm_hour + t.tm_mday + t.tm_mon + t.tm_year + randint(4000);
	srand(seed);
}

void Cave::BuildTunnels()
{
	// adj1 - next room clockwise in the current circle
	// adj2 - next room counterclockwise in the current circle
	// adj3 - room is one step further to the inner/outer circle than the current circle
	// inner circle
	for (int i = 0; i < roomsInCircle; i++) {
		int next = (i + 1) % roomsInCircle;
		rooms[i].adj1 = next;
		rooms[next].adj2 = i;
		rooms[i].adj3 = i + roomsInCircle;
		rooms[i + roomsInCircle].adj3 = i;
	}
	// outer circle
	for (int i = numberOfRooms - roomsInCircle; i < numberOfRooms; i++) {
		int next = ((i + 1) % roomsInCircle) ? i + 1 : i + 1 - roomsInCircle;
		rooms[i].adj1 = next;
		rooms[next].adj2 = i;
	}
	// remaining circles
	for (int i = 0; i < sizeOfCave; i++) {
		for (int j = i * roomsInCircle * 2 + roomsInCircle; j < i * roomsInCircle * 2 + roomsInCircle * 2; j++) {
			rooms[j].adj1 = j + roomsInCircle;
			rooms[j + roomsInCircle].adj2 = j;
		}
		for (int j = i * roomsInCircle * 2 + roomsInCircle * 2; j < (i + 1) * roomsInCircle * 2 + roomsInCircle; j++) {
			int next = ((j - 4) % roomsInCircle) ? j - 4 : j - 4 - roomsInCircle;
			rooms[j].adj1 = next;
			rooms[next].adj2 = j;
			rooms[j].adj3 = j + roomsInCircle;
			rooms[j + roomsInCircle].adj3 = j;
		}
	}
	// assign room numbers
	vector<bool> numbers;
	numbers.resize(firstRoom + numberOfRooms, false);
	for (int i = 0; i < numberOfRooms; i++) {
		int n = GetRandomRoomNumber(numbers);
		rooms[i].num = n;
		ref[n] = i;
	}
}

// range [first : last]
inline int Cave::NextRoom(int first, int last, int n) const
{
	return (n >= last) ? first : n + 1;
}

int Cave::GetRandomRoomNumber(vector<bool>& numbers)
{
	int n = randint(firstRoom, lastRoom + 1);
	while (numbers[n]) n = NextRoom(firstRoom, lastRoom, n);
	numbers[n] = true;
	return n;
}

void Cave::PrintMap() const
{
	constexpr int indentNum = 2;
	cout << endl << line_c60 << endl;
	cout << space_c8 << "You are" << inRoom_c10 << hRoom << endl;
	cout << space_c8 << "Wumpus is" << inRoom_c10 << wRoom << endl;
	cout << space_c8 << "Pit is" << inRoom_c10 << pRoom << endl;
	cout << space_c8 << "Bat is" << inRoom_c10 << bRoom << endl << endl;
	for (int j = firstRoom; j <= lastRoom; j++) {
		for (int i = 0; i < nRooms; i++) {
			if (j == rooms[i].num) {
				int adj1 = rooms[ref[j]].adj1;
				int adj2 = rooms[ref[j]].adj2;
				int adj3 = rooms[ref[j]].adj3;
				cout << space_c8 << room_c6 << setw(indentNum) << right << j << colon_c2 << tunnel_c10
					<< setw(indentNum) << rooms[adj1].num << ", "
					<< setw(indentNum) << rooms[adj2].num << ", "
					<< setw(indentNum) << rooms[adj3].num << endl;
			}
		}
	}
	cout << line_c60 << endl;
	int count[numberOfRooms];
	for (int i = 0; i < numberOfRooms; i++) count[i] = 0;
	for (int i = 0; i < numberOfRooms; i++) {
		count[rooms[i].adj1]++;
		count[rooms[i].adj2]++;
		count[rooms[i].adj3]++;
	}
	for (int i = 0; i < numberOfRooms; i++) {
		if (count[i] != numberOfTunnels) error("Error. Number of tunnels != ", numberOfTunnels);
	}
}

int Cave::GetRandomNextRoom(int prevRoom, int currentRoom) const
{
	while (true) {
		int n = randint(firstRoom, lastRoom + 1);
		if ((ref[n] == rooms[ref[currentRoom]].adj1 || ref[n] == rooms[ref[currentRoom]].adj2
			|| ref[n] == rooms[ref[currentRoom]].adj3) && n != prevRoom) return n;
		continue;
	}
}

bool Cave::IsValidNextRoom(int currentRoom, int nextRoom) const
{
	if (nextRoom < firstRoom || nextRoom > lastRoom) return false;
	if (ref[nextRoom] == rooms[ref[currentRoom]].adj1 || ref[nextRoom] == rooms[ref[currentRoom]].adj2
		|| ref[nextRoom] == rooms[ref[currentRoom]].adj3) return true;
	return false;
}

bool Cave::ParseInput(const string& s, Action& a) const
{
	istringstream iss;
	iss.str(s);
	char type;
	if (!iss.get(type)) return false;
	switch (type) {
	case 'm': {
		a.type = ActionType::MOVE;
		int room1;
		if (!(iss >> room1)) return false;
		if (!IsValidNextRoom(hRoom, room1)) return false;
		a.room1 = room1;
		break;
	}
	case 's': {
		a.type = ActionType::SHOOT;
		int room1, room2, room3;
		char hyphen;
		if (!(iss >> room1)) return false;
		if (!IsValidNextRoom(hRoom, room1)) return false;
		if (iss.get(hyphen) && hyphen == '-') {
			if (!(iss >> room2)) return false;
			if (!IsValidNextRoom(room1, room2)) return false;
			if (room2 == hRoom) return false;
		}
		else room2 = GetRandomNextRoom(hRoom, room1);
		if (iss.get(hyphen) && hyphen == '-') {
			if (!(iss >> room3)) return false;
			if (!IsValidNextRoom(room2, room3)) return false;
			if (room3 == room1) return false;
		}
		else room3 = GetRandomNextRoom(room1, room2);
		a.room1 = room1;
		a.room2 = room2;
		a.room3 = room3;
		break;
	}
	case 'p':
		a.type = ActionType::PRINTMAP;
		break;
	default:
		return false;
	}
	return true;
}

void ClearInput(istream& is)
{
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}
