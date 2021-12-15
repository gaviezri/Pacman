#include "Board.h"

const short STUCK = -1;
bool const to_X = true;
bool const to_Y = false;

unsigned short Board::total_maps = 0;


void Board::getScreen_names()
{
	string tmp_path;
	for (auto const& entry : filesystem::directory_iterator("."))  // goes throu all files in the working directory
	{
		tmp_path = entry.path().string();
		if (tmp_path.length() > 9 && tmp_path.substr(tmp_path.length() - 7) == ".screen")    // checkes if path ends with ".screen
		{
			screen_files.push_back(entry.path().string());          // if so it adds the path to the path container
		}
	}
}

void Board::CreateOrg_maps()
{
	string tmp_line;
	short cur_map = 0;

	std::sort(screen_files.begin(), screen_files.end());
	total_maps = screen_files.size();
	screen_files.shrink_to_fit();
	for (const auto& cur_path : screen_files)    // opens all files and scans them RAW
	{
		ifstream myFile(cur_path, ios_base::in);
		Org_maps.push_back(vector<string>());

		while (!myFile.eof()) {
			getline(myFile, tmp_line);

			if (tmp_line.length() > MAXBOARD_WIDTH)
				Org_maps[cur_map].push_back(tmp_line.substr(0, 79));
			else
				Org_maps[cur_map].push_back(tmp_line);
		}
		myFile.close();
		++cur_map;
	}
	loadNew_map();  //loads the first map
}
Board::Board()   // loads all game board to maps vector
{
	
	getScreen_names();
	if (!screen_files.size())  // if no map files was found
	{
		cout << "WARNING 9345: It seems that there are no valid map files in the working directory " << endl << "              [ the file must end with 'screen' ]";
		Sleep(4000);
	}
	else
		CreateOrg_maps();
}

void Board::setCur_row_len()
{// incase a '&' is the on top , set the legend's dimensions as map's default
	if (Org_maps[active_map][0][0] == '&' && Org_maps[active_map][0].length() == 1)
		cur_rows_len = 20;
// otherwise, the first row sets the tone
	else
		cur_rows_len = Org_maps[active_map][0].length();
}
void Board::loadNew_map()
{
	breadcrumbs = 0;
	pacman_flag = false;
	legend_flag = false;
	undefined_characters = false;

	if (active_map >= total_maps) return;

	int i = 0,j=0;
	Play_map.clear();
	ghosts.clear();
	rows = Org_maps[active_map].size() > 25 ? 25 : Org_maps[active_map].size();
	Play_map.reserve(rows);
	pacman_flag = false;
	legend_flag = false;
	for (; i < Org_maps[active_map].size() && i<MAXBOARD_HEIGHT ; ++i)
	{	
		if (!i)
			setCur_row_len();
		else
		{
			short originalsize = Org_maps[active_map][i].size();
			Org_maps[active_map][i].resize(cur_rows_len);
			for (int j = originalsize ; j < cur_rows_len; ++j) 
				Org_maps[active_map][i][j] = ' ';
		}
		create_PlayMap_from_Org(i,Org_maps[active_map][i].length());  // initializing visual cells from Original map one row at a time.
		 
	}
	insert_legend();
	if (!pacman_flag)
	{
		system("cls");
		cout << "the map: " << screen_files[active_map] << " does not contain a pacman default position and therefore cannot be loaded.";
		Sleep(3500);
	}
	else if (undefined_characters)
	{
		cout << "the map: " << screen_files[active_map] << " contains a undefined symbols and therefore cannot be loaded.";
		Sleep(3500);
	}

}

void Board::insert_legend_row(const unsigned y, const unsigned x)
{
	for (int i = x; i < x+20 ; i++)
	{
		if (i < Play_map[y].size())
			Play_map[y][i] = static_cast<char>(Content::WALL);
		else
			Play_map[y].push_back('#');
	}
}

void Board::insert_legend()
{
	unsigned short y = legend.getY(), x = legend.getX();

		if (y < Play_map.size() && x < Play_map[y].size())
		{
			insert_legend_row(y, x);
		}
		if (y+1 < Play_map.size() && x < Play_map[y+1].size())
		{
			insert_legend_row(y+1, x);
		}
		if (y + 2 < Play_map.size() && x < Play_map[y + 2].size())
		{
			insert_legend_row(y+2, x);
		}
}
	

void Board::create_PlayMap_from_Org(int y, int actual_len)
{
	short tmp = 0;
	Play_map.push_back(Org_maps[active_map][y]);
	for (int x = 0; x < cur_rows_len ; ++x)
	{	//this condition is to double check resize was successful and if not the 'else' part takes care of the compelment needed
		if(x<actual_len)
		switch ((char)Org_maps[active_map][y][x])
		{
		case ' ':
			Play_map[y][x] = '.';
			breadcrumbs++;
			break;
		case '%':
			Play_map[y][x] = ' ';
			break;
		case '$':
			Play_map[y][x] = ' ';
			ghosts.push_back(Ghost(Point(x,y)));  //sets def pos
			break;
		case '@':
			if (!pacman_flag)
			{
				Play_map[y][x] = ' ';
				pac = Pacman(Point(x, y));    //sets def pos
				pacman_flag = true;
			}
			else Play_map[y][x] = '.';
			break;
		case '&':
			if (!legend_flag)
			{
				Play_map[y][x] = ' ';
				legend = Point(x, y);
				legend_flag = true;
			}
			break;
		case '#':
			continue;
		default:
			undefined_characters = true;
			break;
		}
		else
			Play_map[y].push_back(' ');
	}
}

void Board::printMap(bool colored)
{
	for (int i = 0; i < Play_map.size(); ++i) { if (colored) setTextColor(Color::BLUE); else setTextColor(Color::WHITE);  cout << Play_map[i] << endl; }
}

void Board::move_in_border(Direction& next_dic, Direction& cur_dic, Direction& last_dic,const bool & colored, short& score)
{
	if (next_dic == Direction::STAY)// pac is now frozen on the current cell until next input is recieved
		cur_dic = Direction::STAY;

	else if (int(Content::WALL) != nextCellCont(pac.getPos(), next_dic))  //advance to next direction if its not a wall
	{
		movePac(next_dic, colored, score);
		last_dic = cur_dic = next_dic;// remember the new direction
		next_dic = Direction::DEF; // default the next direction
	}
	else if (portals(cur_dic, next_dic, (Point&)pac.getPos()))
	{
		pac.printMe(colored);
	}
	else if (int(Content::WALL) != nextCellCont(pac.getPos(), cur_dic)) // advance in current direction if the 
	{																	       // requested next isnt possible
		movePac(cur_dic, colored, score);
		last_dic = cur_dic;
	}
}

void Board::movePac(Direction dic, bool colored, short& score)
{
	char cell_c = nextCellCont(pac.getPos(), dic);
	pac.updateMove(dic, colored);
	if (cell_c == '.')
	{
		score++;
		changeFood2Path(pac.getPos());
	}
}



bool Board::isInBorder(Point pos)
{
	unsigned short X = pos.getX(), Y = pos.getY();
	if (Y >= rows || Y<0) return false;
	return ((X >= 0 && X<=cur_rows_len - 1) &&  (Y >= 0 &&  Y <= rows-1 ));
}

bool Board::isOnBorder(Point pos)
{
	unsigned short X = pos.getX(), Y = pos.getY();
	if (isTopBorder(pos.getX(), pos.getY()))
		return true;
	return (X == 0 || Y == 0 || X == cur_rows_len - 1 || Y == rows - 1 );
}



void Board::AnalyzeAround(NPC& g, char* conts, bool* paths)
{
	int i = 0;
	Point gPos = g.getPos();
	unsigned short Y = gPos.getY(), X = gPos.getX();

	// first round of check makes sure we approach legal indexing
	if (isInBorder(Point(X, Y - 1))) conts[int(Direction::UP)] = Play_map[Y - 1][X];	//assigning the array of the cells content around current ghost
	else conts[int(Direction::UP)] = (char)Content::WALL;

	if (isInBorder(Point(X, Y + 1))) conts[int(Direction::DOWN)] = Play_map[Y + 1][X]; // position on the beggining of her move.
	else 	conts[int(Direction::DOWN)] = (char)Content::WALL;
	
	if (isInBorder(Point(X - 1, Y))) conts[(int)Direction::LEFT] = Play_map[Y][X - 1];
	else conts[(int)Direction::LEFT] =(char)Content::WALL;

	if (isInBorder(Point(X + 1, Y))) conts[(int)Direction::RIGHT] = Play_map[Y][X + 1];
	else conts[(int)Direction::RIGHT] = (char)Content::WALL;

	for ( i = 0; i < 4; i++)
	{
		if (conts[i] == (char)Content::WALL)
		{
			paths[i] = false;
		}
		else
			paths[i] = true;
	}
}

void getOptions(vector<Direction>& d, bool* paths)
{
	d.clear();
	for (int j = 0; j < 4; ++j)
		if (paths[j])  d.push_back((Direction)j);
}

void Board::nextContAndOppDic(Direction dic, Direction& op_dic, char& next_cont, char* cont_around)
{
	switch (dic)
	{
	case Direction::UP:
		op_dic = Direction::DOWN;
		next_cont = cont_around[(int)Direction::UP];
		break;
	case Direction::DOWN:
		op_dic = Direction::UP;
		next_cont = cont_around[(int)Direction::DOWN];
		break;
	case Direction::LEFT:
		op_dic = Direction::RIGHT;
		next_cont = cont_around[(int)Direction::LEFT];
		break;
	case Direction::RIGHT:
		op_dic = Direction::LEFT;
		next_cont = cont_around[(int)Direction::RIGHT];
		break;
	default:
		op_dic = Direction::DEF;
		break;
	}
}

char Board::nextCellCont(Point pos, Direction dic)
{
	unsigned short x = pos.getX(), y = pos.getY();

	switch (dic)
	{
	case Direction::UP:
		if (y != 0) return (Play_map[--y][x]);
		return static_cast<char>(Content::WALL);
		break;
	case Direction::DOWN:
		if (Play_map.size()-1 <= y) return static_cast<char>(Content::WALL); // if the board has no limits the pacman will consider as walls
		return (Play_map[++y][x]);
		break;
	case Direction::LEFT:
		if (x != 0) return (Play_map[y][--x]);
		return static_cast<char>(Content::WALL);
		break;
	case Direction::RIGHT:
		if (Play_map[y].length()-1 <= x) return static_cast<char>(Content::WALL); // if the board has no limits the pacman will consider as walls
		return (Play_map[y][++x]);
		break;
	default:
		return static_cast<char>(Content::WALL);
		break;
	}
}


void Board::premoveDatacollection(char& next_cont,char* cont_around, bool* path_around, NPC& G, Direction& opposite_dic,vector<Direction>& options)
{
	G.setCont_under ( Play_map[G.getPos().getY()][G.getPos().getX()]);// gets the content that the ghost 'steps' on prior to new location

	AnalyzeAround(G, cont_around, path_around);

	nextContAndOppDic(G.getcurDic(), opposite_dic, next_cont, cont_around);//checking whats the next cell's content in the current direction im going and 
																		  // updating my opposite direction
	path_around[(int)opposite_dic] = false;  // We want the ghost to treat the opposite direction as if it was a wall.

	getOptions(options, path_around);
}

void Board::NPCmoveGenerator(bool colored,int movesmade,unsigned short& fruitbonus)
{
	char cont_around[4], next_cont ;		//wall counter count actual walls, path around just indicate wether there is a path and we are manipulating the opposite direction to act
	vector<Direction> options;
	Direction opposite_dic;
	bool path_around[4];             // bool array that indicate by index using enum if theres a path in a given direction
	if(movesmade%2 && ghosts.size())
	for (auto& G : ghosts)//moving ghosts
	{
		
		premoveDatacollection(next_cont, cont_around, path_around, G, opposite_dic, options);
		switch (Ghost::getDif())
		{
		case Difficulty::NOVICE:
			NoviceMovement(options, opposite_dic, next_cont, colored, G);
			break;
		case Difficulty::GOOD:
			if (movesmade % 20 > 14) NoviceMovement(options, opposite_dic, next_cont, colored, G);
			else BestMovement(options, colored, G,opposite_dic,next_cont);
			break;
		case Difficulty::BEST:
			BestMovement(options, colored, G, opposite_dic, next_cont);
			break;
		}
	
	}
	premoveDatacollection(next_cont, cont_around, path_around, fruit, opposite_dic, options);
	if (fruit.isAppearing())
	{
		if ((movesmade % 4) == 1)
		{
			NoviceMovement(options, opposite_dic, next_cont, colored, fruit);
			fruit.step();
			pacEatsfruit(fruitbonus);
		}
		fruit.Disappear(getvalidPos());
	}	
	else
	{
		if(fruit.ExposeMe())
			fruit.Appear();
		NoviceMovement(options, opposite_dic, next_cont, colored, fruit);
		fruit.Disappear(getvalidPos());
	}
}

void Board::pacEatsfruit(unsigned short& fruitscore)
{
	if (fruit.getPos() == pac.getPos())
		fruitscore += (fruit.Eaten(getvalidPos()) - IntToChar);
}



void Board::NoviceMovement(const vector<Direction>& options,const Direction& opposite_dic, const const char& next_cont, bool colored, NPC& G)
{
	if (next_cont == (int)Content::WALL) //  + Or T Or L Or  or DeadEnd  junction approaching T from side or from front
		switch (options.size())
		{
		case 0:	// Dead-End go opposite direction
			G.updateMove(G.setcurDic(opposite_dic), colored);
			break;
		case 1:	//L Junc  - go the only way 
			G.updateMove(G.setcurDic(options[0]), colored);
			break;
		default:	//T Junc choose randomly from options
			G.updateMove(G.setcurDic(options[rand() % (options.size())]), colored);
			break;
		}
	else if (options.size() >= 2)// in a 4 way junc - choose randomly
		G.updateMove(G.setcurDic(options[rand() % (options.size())]), colored);
	else
		G.updateMove(G.getcurDic(), colored);// continue same way
}
inline bool stuck4ways(int up, int down, int left, int right)
{
	return (up == STUCK) && (down == STUCK) && (left == STUCK) && (right == STUCK);
}
inline Direction shortestRoute(int up, int down, int left, int right)
{
	if(stuck4ways(up,down,left,right)) return Direction::DEF;//incase pacman is hiding on edges (this is the logic.)

	if (up == STUCK) up = 1 + max(max(down, left), right);// ensuring STUCK assigned values will not be the minimals
	if (down == STUCK) down = 1 + max(max(up, left), right);
	if (left == STUCK) left = 1 + max(max(down, up), right);
	if (right == STUCK) right = 1 + max(max(down, up), left);
	
	if (up == (min(min(up, down), min(left, right)))) return Direction::UP; // returning direction of a shortest path (can be 1 or more)
	if (down == (min(min(up, down), min(left, right)))) return Direction::DOWN;
	if (left == (min(min(up, down), min(left, right)))) return Direction::LEFT;
	if (right == (min(min(up, down), min(left, right)))) return Direction::RIGHT;
}

void Board::BestMovement(const vector<Direction>& options,const bool& colored, Ghost& G,const Direction& opposite_dic,const char& next_cont) // smart ghosts movement maker
{// getting the length of paths to pacman from all 4 direction and choosing the direction with the shortest 
//  path.  if pacman is hiding in borders with no portals the ghosts will lose his location and go randomly
//	giving the sensation they are looking for him
	Point dest = pac.getPos();  
	int UP = BestMovement_Util(dest, G.getPos() - Point(0, 1)); 
	int DOWN = BestMovement_Util(dest, G.getPos() + Point(0, 1));	
	int LEFT = BestMovement_Util(dest, G.getPos() - Point(1, 0));
	int RIGHT = BestMovement_Util(dest, G.getPos() + Point(1, 0));
	Direction tmp = shortestRoute(UP, DOWN, LEFT, RIGHT);
	if (tmp == Direction::DEF)
		NoviceMovement(options, opposite_dic, next_cont, colored, G);
	else
	G.updateMove(tmp,colored);
}

vector<vector<bool>> Board::createTrackingMap()
{//initializing the bool matrix which represent where ghost cango when bfs
	vector<vector<bool>> canGo;

	canGo.reserve(rows);

	for (int row = 0; row < rows; row++)
	{
		vector<bool> tmp;

		for (int col = 0; col < Play_map[row].length(); col++) //creation here
		{// wall = false, otherwise = true;
			if (isInBorder(Point(col, row)))  
				if (Play_map[row][col] == (int)Content::WALL)
					tmp.push_back(false);
				else
					tmp.push_back(true);
			else 
				tmp.push_back(false);

		}
		canGo.push_back(tmp);
	}
	return canGo;
}

int Board::BestMovement_Util( Point dest, Point cur)
{
    vector<vector<bool>> canGo = createTrackingMap(); // create a boolean map the reflects where can go
	if (!isInBorder(cur) || !canGo[cur.getY()][cur.getX()] || isOnBorder(cur) ) 
		return STUCK;
	queue<pair<Point, int>> steps; //keeping visited cells here to get back to them while exploring the breadth
																								
	steps.push({ cur,0 }); 
	while (!steps.empty())
	{
		pair<Point, int> tmp = steps.front();
		steps.pop();
		if (isOnBorder(tmp.first))
		{
			continue;
		}
		// falsify my position preventing circles while tracking (like hensel and gretel leaving bread crumbs behind)
		canGo[cur.getY()][cur.getX()] = false;
		if (tmp.first == dest)
			return tmp.second;
		
		if (isInBorder(tmp.first - Point(0, 1))) // GOING UP
			if (canGo[tmp.first.getY() - 1][tmp.first.getX()])
			{
				canGo[tmp.first.getY() - 1][tmp.first.getX()] = false;
				steps.push({ tmp.first - Point(0, 1),tmp.second + 1 });
			}
			
		if (isInBorder(tmp.first + Point(0, 1))) // DOWN
			if (canGo[tmp.first.getY() + 1][tmp.first.getX()])
			{
				canGo[tmp.first.getY() + 1][tmp.first.getX()] = false;
				steps.push({ tmp.first + Point(0, 1),tmp.second + 1 });
			}

		if (isInBorder(tmp.first - Point(1, 0))) // LEFT
			if (canGo[tmp.first.getY()][tmp.first.getX() - 1])
			{
				canGo[tmp.first.getY()][tmp.first.getX() - 1] = false;
				steps.push({ tmp.first - Point(1, 0),tmp.second + 1 });
			}

		if (isInBorder(tmp.first + Point(1, 0)))
			if (canGo[tmp.first.getY()][tmp.first.getX() + 1])// RIGHT
			{
				canGo[tmp.first.getY()][tmp.first.getX() + 1] = false;
				steps.push({ tmp.first + Point(1, 0),tmp.second + 1 });
			}
	}
	return STUCK;	
}






bool Board::Collision()
{
	for (auto g : ghosts)
	{
		if (pac.getPos().getX() == g.getPos().getX() && pac.getPos().getY() == g.getPos().getY())
			return true;
	}
	return false;
}

bool Board::isTopBorder(const unsigned& X, const unsigned& Y)
{//checking if a give cell is a top border (relatively)
	unsigned short y;
	if (Y == 0)
		return true;
	
	if (legend.getY() < Y)
	{
		findBorder_Top(X, y);
		if (y == Y)
			return true;
	}
	if (Y > 0 && (Play_map[Y - 1].length() < Play_map[Y].length()))
		return (X > Play_map[Y - 1].length());
	return false;

}
bool Board::isportal(const unsigned short& X, const unsigned short& Y)
{
	if (Y > 0)
		return (Play_map[Y - 1][X] == static_cast<char>(Content::WALL) && Play_map[Y + 1][X] == static_cast<char>(Content::WALL)
			&& isBlank(Play_map[Y][X]));
			return false;
}
bool Board::portals(Direction& dic,Direction& next_dic,Point& pos)
{
	unsigned short X = pos.getX();
	unsigned short Y = pos.getY();
		// print ' ' over pac's last position and update his coord to other side
	
	if (X == 0 && (dic == Direction::LEFT || next_dic == Direction::LEFT) && isBlank(Play_map[Y][cur_rows_len-1] ))// Left -> Right
	{// print ' ' over pac's last position and update his coord to other side
		pac.clearMe();
		pac.setX(Play_map[Y].length() - 1);
		next_dic = dic;
		return true;
	}
	else if (X == cur_rows_len-1 && (dic == Direction::RIGHT || next_dic == Direction::RIGHT) && isBlank(Play_map[Y][0])) //Right -> Left
	{
		pac.clearMe();
		pac.setX(0);
		next_dic = dic;
		return true;
	}
	else if (Y==0 && (dic == Direction::UP || next_dic == Direction::UP) && isBlank(Play_map[rows - 1][X]))// TOP -> BOTTOM
	{
		pac.clearMe();
		pac.setY(rows-1);
		next_dic = dic;
		return true;
	}
	else if (Y == rows-1 && (dic == Direction::DOWN || next_dic == Direction::DOWN) && isBlank(Play_map[0][X])) // BOTTOM -> UP
	{
		pac.clearMe();
		pac.setY(0);
		next_dic = dic;
		return true;
	}
	return false;
}

 bool Board::findBorder_Top(const unsigned short& col,unsigned short & line )
{
	 unsigned short lgnd_x = legend.getX(), lgnd_y = legend.getY();
	 for (int i = 0; i < Play_map.size(); ++i)//looking for the row which is the top border relative to the coloumn im in.
		 if (Play_map[i].size() >= col)			// if the current from top is potentially a portal 
		 {
			 if(i==lgnd_y && col >= lgnd_x && col <=lgnd_x+20)
			 {// skip legend rows if needed to find the portal on the other side
				 i += 2; 
				 continue;
			 }
			 if (isBlank(Play_map[i][col]))
			 {
				 line = i;
				 return true;
			 }
			 return false;
		 }
	 return false;
}

