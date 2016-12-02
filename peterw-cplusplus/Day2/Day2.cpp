// Advent of Code 2016 - Day2
// Peter Westerstr�m

#include <cassert>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

using namespace std;

struct Move
{
public:
	Move(char dir, int digit)
		: dir{dir}
		, digit{digit}
	{
	}

	char dir;
	int digit;
};

bool operator==(const Move& l, const Move& r)
{
	return l.dir==r.dir && l.digit==r.digit;
}

namespace std
{
	template<>
	struct hash<Move>
	{
		size_t operator()(const Move& k) const
		{
			return hash<char>()(k.dir) ^ hash<int>()(k.digit);
		}
	};
}

unordered_map<Move, int> moveMap {
	{{'L', 1}, 1}, 	{{'L', 2}, 1}, 	{{'L', 3}, 2},
	{{'L', 4}, 4}, 	{{'L', 5}, 4}, 	{{'L', 6}, 5},
	{{'L', 7}, 7}, 	{{'L', 8}, 7}, 	{{'L', 9}, 8},

	{{'R', 1}, 2}, 	{{'R', 2}, 3}, 	{{'R', 3}, 3},
	{{'R', 4}, 5}, 	{{'R', 5}, 6}, 	{{'R', 6}, 6},
	{{'R', 7}, 8}, 	{{'R', 8}, 9}, 	{{'R', 9}, 9},

	{{'U', 1}, 1}, 	{{'U', 2}, 2}, 	{{'U', 3}, 3},
	{{'U', 4}, 1}, 	{{'U', 5}, 2}, 	{{'U', 6}, 3},
	{{'U', 7}, 4}, 	{{'U', 8}, 5}, 	{{'U', 9}, 6},

	{{'D', 1}, 4}, 	{{'D', 2}, 5}, 	{{'D', 3}, 6},
	{{'D', 4}, 7}, 	{{'D', 5}, 8}, 	{{'D', 6}, 9},
	{{'D', 7}, 7}, 	{{'D', 8}, 8}, 	{{'D', 9}, 9}
};

string solveDay2(string input)
{
	string passcode;
	accumulate(input.begin(), input.end(), 5, 
			   [&passcode](int current, char dir) {
		if(dir=='\n')
		{
			passcode += ('0' + current);
			return current;
		}
		assert(dir== 'R' || dir=='L' || dir=='U' || dir=='D');
		return moveMap[Move{dir, current}];
	});

	cout << "Day2 solution: " << passcode << endl;
	return passcode;
}

string day2_testinput = R"rawstring(ULL
RRDDD
LURDL
UUUUD
)rawstring";

string day2_input = R"rawstring(RRLLDDRLLDURLDUUDULDLRLDDDRLDULLRDDRDLUUDLLRRDURRLUDUDULLUUDRUURRDDDDURUULLDULRLRRRDLLLRDLRDULDLRUUDRURLULURUUDRLUUDRDURUUDDDRDLLRDLUDRLUUUUUULDURDRDDURLDDRLUUDLRURRDRLDRDLRRRLURULDLUUURDRLUULRDUDLDRRRDDLDDDRLRLLDRDUURDULUURRRRUDLLUDLDRLLRRULLLRDRDRRDRDRDUULUDLULRLLDRULURLURDLLDDRRLUDRDUULLDRULLLRLULUDDLURLUULDRUDRLDUUDDLLLRURDRLDRLUUUUUUDRUDLDLULULRRURRDDDUDRRRDDDLDDLRLLDDUULLUDRURDDDRDDLURRURULULUUDRLLUUDDDRUULRDLDLLRUUDRRLRRRULLRRURUDDUUDULDUDUUUDURUDUUDUDRULUDULRDUDUUUUDLLURDLRRUDURDDUULLDLLRDUDULRLRDURLRDRDLRDLRURUDURLULDDDLDRLULLRLURRLLDLRLLULLDUURUUDRULDDUDLDDR
LUURULURUURRRDLRDRDDDUDULRDDLUUDUUULRLRRLRUDDLDLURLRULUUDUUDLDRLLUURLUUURDUDLUULLUUDUUDRDUDUDURLLURDUDLDLDDLDUDRLLUULDDRUDDDRLRUDRDUDULLRRDLLDDLRLLLRLRURURLLDULUDDUULULDRRLUURDULRULUDULDULDULRULLLRRDRLDRLDUULLDDULRLUDLLLULDDLULLUULUURRULDLUULDRRUDDDLRDLULDULDRRDLRRRLRUDURUDDDUDDURRRLDUULRDDLRRRLRUULDDURDRDUULDLLULULDRDRUULDLULRUUDUDLUDRLRDURRRRLULURDRLLLUDRRRDRURRLRLLUURDLURLURDULURUDDULLDUUDDLRLUULRDUUDRDRUDRLUUUDURLLRDRRDRURDDDDULLDDUDLDUUDLRLURURLDRRDRDUDLRRDRUDRDLURRLLLULULULRUDDDULULULDDRRLULUUUURDDURURLDLDDDDDRULUUUULLUDDDRRLUULDUULRUUDUURRLLRDDRUURL
RRRLLLLUULLRRLLDRULULLLRDLLDLDDLURUDLULUULLRURLDULLUDULDRURDURLULLDUDDRLLRUURDLLULUURLULLDLRRDDDULUURRUDRDRDURULDLLURUDLLLDDUDLLLLRLDRDRDDRRDLUUDLLLULLLLLDDRDLULLLLRURRRUUUULLDLRDLDLRRRULRRRRLDLLRDURULDDLURURUULULDRDDDURLRDDRDULLUURUDUUUDRDRRLURULULRLUUDDRDULDRLULULUULRLDRLUDRRDDDRUDDRDDRDDRRLRDLRURDULULRRUUURDRRRDURDDRUDULUUDRDDLDRDDDULDLRDUULDUULRUDLRRDDDLLDDLLLRRDLDUULUULULURRULLRRUDUDRUDRRRLDLRLURRLUDLLLUUDDUDRURUUDDURDURULRLDUDRDLULDUDRUDDDR
DRDRRUUUUURRLUDLDLRUUULRLDLRRRDDUDLUUDUDDLRDUDLRRLLURUUDULLUDLULLDLLDDULUDDUDUULURLDLDDUUDDRDDRLUURLUUDUDUDURULLDRLDDRUDLURRRLDRLRULDDLDDLDDDULDUDDLLDULUUDUDDUULDRLDRLRURDULUDDRRLRRLRRDULDRRDUDUDRLDURRLRLRDLRLRRLRDDDRULLULULDUDDLDLULRLLURRRRULUULRUDLDLRDLLURURUUURDRRRLDDRLRLURDDURDDUURUUUDDLRUURRRDLLUULUDRLDDRDDDDUUDRLRRDULDULRDLLLRULULLRDRULLRDLRUUURRRURLRRDLDRDDLURLDLULLDUURRDULUUURRLLDDUUUULDDDDLRDDDRDLDLLUURLDDRULUDDRDDDLRDU
DRRRLURUDUDUULDLLURLUUDDRRRDUDLURLLDRRLLDDURULUDUURURULLRLDLLUURDLLDLLDLDLRUDLLLLDRLLUDLLDULDDRRURDRRLRLRRUURRUDURRLDRDLDURUULUDRLLURLUDURDULLRLLDLURLRRDLLLLUUDRDULLDLURDULDRDURRRLDRLURULULURLLLRRRUULRLRRDRDDDLULRLRRDLUDDUUUUUDRRDLDUDUURLDRRRLRUDRULDRLURUULRDLDDLRURDLURULRRLDURLDUURURULRDUDRRUDUDDLRLUURURULDDLULULULDULRRLRRURUURLRLLDRRLUDLUURDRRURRUUDULRLURRLRLRDDRURDDLRRDUDRLLUUUDULRDRULUURRLRLRDUDULDRDLLUDRDLLDRULDLUUURDDRDDUDDULLLDRRDDUDDDDLDDRLRULRRRURRDRULLDDDURDDLURRDDDUDLURRUDUDLLDDDLRUUDRLRRLRDUUUDDL
)rawstring";


int main()
{
	//solveDay2(day2_testinput);
	solveDay2(day2_input);
	return 0;
}