#include <roguelib.h>
#include <curses.h>
#include <cstring>
#include <iostream>

int main()
{
	// touche pour quitter
	const char KEY_QUIT = 'q';

	// touche pour éteindre le feu
	const char KEY_SPACE = ' ';

	// constantes pour murs, joueur et feux
	const char WALL = 'X';
	const char PLAYER = '@';
	const char SPIKEUP = '^';
	const char SPIKEDOWN = ' ';
	const char LEVEROFF = '/';
	const char LEVERON = '"\"';
	const char DOORUPDOWN = 'D';
	const char DOORLEFTRIGHT = 'd';
	const char DOORLOCKED = 'L';
	const char LASERON = '|';
	const char LASEROFF = ' ';
	const char CHAIR = 'h';
	const char TRONE = 'H';
	const char FIREBOWL = 'Y';
	const char PLATE = '#';
	const char CHEST = '$';
	const char KNIGHT = 'K';
	const char CORPSE = 'k';
	const char CHESTCLOSE = 'C';
	const char CHESTOPEN = 'c';
	const char FULLTRONE = '¤';
	const char TELEPORTER = 'P';
	

	// dimensions de la grille
	const int COLS = 40;
	const int ROWS = 20;

	// level design
	char grid[ROWS][COLS + 1] =
	{
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XDXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X        dXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X        XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X        XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	};

	char BaseLevel[ROWS][COLS + 1] =
	{
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X             d    X       X           X",
		"X             X    X       X           X",
		"XDXXXXXXXXXXXXX    X   P   X     /     X",
		"X X      d    X    X       X           X",
		"X XXXXXXXX    X    X       X           X",
		"X   Kd   X    X    X       X           X",
		"X    XC  X    X    XXXXXXXXX           X",
		"X    XXXXX    X    X       d           X",
		"X    X        X    d       X           X",
		"XXDXXXXXXXXXDXX    X       X           X",
		"X             d    XXXXXXDXXXXXXXXXXXXXX",
		"X      #      X    X   X               X",
		"X             X    d   X               X",
		"X             X    XXXXXXXXXXXXXXXDXXXXX",
		"XDXXXXXXXXXXXXXXXXDX         X         X",
		"X        d         d         X         X",
		"X        XXXXXXDXXXXXXLXXXLXXX         X",
		"X        X           X  hX   X         X",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	};

	init_pair('X', COLOR_WHITE, COLOR_BLACK);
	init_pair('d', COLOR_BLACK, COLOR_WHITE);
	init_pair('D', COLOR_BLACK, COLOR_WHITE);
	init_pair('L', COLOR_BLACK, COLOR_WHITE);
	init_pair('K', COLOR_BLACK, COLOR_GREEN);
	init_pair('k', COLOR_BLACK, COLOR_MAGENTA);
	init_pair('#', COLOR_BLUE, COLOR_WHITE);
	init_pair('h', COLOR_BLUE, COLOR_WHITE);
	init_pair('C', COLOR_BLUE, COLOR_WHITE);
	init_pair('C', COLOR_WHITE, COLOR_BLUE);
	// vous pouvez utiliser les valeurs déjà connues:
	// COLOR_BLACK   0
	// COLOR_RED     1
	// COLOR_GREEN   2
	// COLOR_YELLOW  3
	// COLOR_BLUE    4
	// COLOR_MAGENTA 5
	// COLOR_CYAN    6
	// COLOR_WHITE   7

	// crée une nouvelle couleur rouge vif (doit être plus grand que 7)
	init_color(/* numéro de la nouvelle couleur */ 8, /* rouge */ 1000, /* vert */ 250, /* bleu */ 250);
	// maintenant R représente cette couleur
	init_pair('R', 8, COLOR_BLACK);

	// tableau de couleurs
	char colors[ROWS][COLS + 1] =
	{
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XDXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X        dXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X        XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"X        XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	};
	// position de départ
	int x = 2, y = 17;
	// Variables du joueur
	bool combat = false;
	bool carryCorpse = false;
	bool carryChair = false;
	bool key = false;
	int win = 0;

	bool quit = false;
	do
	{
		// fait une copie du résultat du level + position du joueur
		char render[ROWS][COLS + 1];
		std::memcpy(render, grid, sizeof(grid));
		render[y][x] = PLAYER;

		std::string message;
		if (grid[y][x] == DOORUPDOWN && (grid[y+1][x] == WALL || grid[y-1][x] == WALL))
		{
			message = "Press SPACE to open the door.";
		}

		if (grid[y][x] == DOORLEFTRIGHT && (grid[y][x + 1] == WALL || grid[y][x - 1] == WALL))
		{
			message = "Press SPACE to open the door.";
		}

		if (grid[y][x] == KNIGHT)
		{
			combat = true;
			message = "The knight prevent you from moving, press space to kill the knight";
		}

		if (grid[y][x] == CORPSE)
		{
			combat = false;		
			if (grid[12][7] == TRONE)
			{
				message = "The knight is dead press space to take his corpse";
			}
			else
			{
				message = "The knight is dead you left his corpse on the floor";
			}
		}

		if (grid[y][x] == CHESTCLOSE)
		{
			message = "Press space to open the chest and take its content";
		}

		if (grid[y][x] == CHESTOPEN)
		{
			message = "There was a key in the chest, but since you took it, now it's empty";
		}

		if (grid[y][x] == DOORLOCKED && grid[y-1][x] == WALL)
		{
			if (key)
			{
				message = "Press SPACE to open the door with your key.";
			}
			else
			{
				message = "This door is locked but you could open it if you had a key";
			}
		}

		if (grid[y][x] == PLATE)
		{
			if (carryChair)
			{
				message = "Press space to place your chain on the plate";
			}
			else
			{
				message = "There is a plate here with four small indents probably for a chair";
			}
		}

		if (grid[y][x] == TRONE)
		{
			if (carryCorpse)
			{
				message = "Press space to place the dead knight on the throne";
			}
			else
			{
				message = "The throne is empty";
			}

		}

		if (grid[y][x] == FULLTRONE)
		{
			message = "There is someone on the throne even if this someone is dead";
		}

		if (grid[y][x] == LEVEROFF)
		{
			message = "There is an inscription on the lever: Only use if there is someone on the throne";
		}

		if (grid[y][x] == TELEPORTER)
		{
			message = "This teleporter can bring you home, press space to go in";
		}

		if (grid[y][x] == CHAIR)
		{
			message = "This is a chair. Press space to take it";
		}

		// dessine le level
		roguelib::Draw(render, colors, COLS, ROWS, message);


		// lit les touches de clavier
		switch (roguelib::ReadKey())
		{
		case KEY_QUIT:
			quit = true;
			break;

		// déplacement du joueur
		case KEY_UP:    if (y > 0 && grid[y - 1][x] != WALL && !combat) --y; else ; break;
		case KEY_DOWN:  if (y < ROWS - 1 && grid[y + 1][x] != WALL && !combat) ++y; break;
		case KEY_LEFT:  if (x > 0 && grid[y][x - 1] != WALL && !combat) --x; break;
		case KEY_RIGHT: if (x < COLS - 1 && grid[y][x + 1] != WALL && !combat) ++x; break;

		case KEY_SPACE: 
			if (grid[y][x] == DOORUPDOWN || (grid[y][x] == DOORLOCKED && key))
			{
				bool Up = false;
				bool Fini = false;
				int tempX = x;
				int tempY = y;
				if (grid[y + 1][x] == 'X')
				{
					Up = false;
					tempY++;
				}
				else
				{
					Up = true;
					tempY--;
				}

				while (!Fini)
				{
					if (Up)
					{
						while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];

							if (BaseLevel[tempY][tempX - 1] == 'd' || BaseLevel[tempY][tempX - 1] == 'L' || BaseLevel[tempY][tempX - 1] == 'D')
							{
								grid[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
								colors[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
							}
							else if (BaseLevel[tempY][tempX + 1] == 'd' || BaseLevel[tempY][tempX + 1] == 'L' || BaseLevel[tempY][tempX + 1] == 'D')
							{
								grid[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
								colors[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
							}

							if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
							{
								break;
							}
							tempY--;
						}
						tempX = x - 1;
						tempY = y - 1;
						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempY--;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY][tempX - 1] == 'd' || BaseLevel[tempY][tempX - 1] == 'L' || BaseLevel[tempY][tempX - 1] == 'D')
								{
									grid[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
									colors[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
								}
								else if (BaseLevel[tempY][tempX + 1] == 'd' || BaseLevel[tempY][tempX + 1] == 'L' || BaseLevel[tempY][tempX + 1] == 'D')
								{
									grid[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
									colors[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempY--;
							}
							tempX -= 1;
							tempY = y - 1;
						}
						tempX = x + 1;
						tempY = y - 1;

						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempY--;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY][tempX - 1] == 'd' || BaseLevel[tempY][tempX - 1] == 'L' || BaseLevel[tempY][tempX - 1] == 'D')
								{
									grid[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
									colors[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
								}
								else if (BaseLevel[tempY][tempX + 1] == 'd' || BaseLevel[tempY][tempX + 1] == 'L' || BaseLevel[tempY][tempX + 1] == 'D')
								{
									grid[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
									colors[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempY--;
							}
							tempX += 1;
							tempY = y - 1;
						}
					}
					else
					{
						while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];

							if (BaseLevel[tempY][tempX - 1] == 'd' || BaseLevel[tempY][tempX - 1] == 'L' || BaseLevel[tempY][tempX - 1] == 'D')
							{
								grid[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
								colors[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
							}
							else if (BaseLevel[tempY][tempX + 1] == 'd' || BaseLevel[tempY][tempX + 1] == 'L' || BaseLevel[tempY][tempX + 1] == 'D')
							{
								grid[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
								colors[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
							}

							if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
							{
								break;
							}
							tempY++;
						}
						tempX = x - 1;
						tempY = y + 1;
						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempY++;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY][tempX - 1] == 'd' || BaseLevel[tempY][tempX - 1] == 'L' || BaseLevel[tempY][tempX - 1] == 'D')
								{
									grid[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
									colors[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
								}
								else if (BaseLevel[tempY][tempX + 1] == 'd' || BaseLevel[tempY][tempX + 1] == 'L' || BaseLevel[tempY][tempX + 1] == 'D')
								{
									grid[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
									colors[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempY++;
							}
							tempX -= 1;
							tempY = y + 1;
						}
						tempX = x + 1;
						tempY = y + 1;

						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempY++;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY][tempX - 1] == 'd' || BaseLevel[tempY][tempX - 1] == 'L' || BaseLevel[tempY][tempX - 1] == 'D')
								{
									grid[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
									colors[tempY][tempX - 1] = BaseLevel[tempY][tempX - 1];
								}
								else if (BaseLevel[tempY][tempX + 1] == 'd' || BaseLevel[tempY][tempX + 1] == 'L' || BaseLevel[tempY][tempX + 1] == 'D')
								{
									grid[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
									colors[tempY][tempX + 1] = BaseLevel[tempY][tempX + 1];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempY++;
							}
							tempX += 1;
							tempY = y + 1;
						}
					}
					Fini = true;						
				}
			}
			else if (grid[y][x] == DOORLEFTRIGHT)
			{
				bool Left = false;
				bool Fini = false;
				int tempX = x;
				int tempY = y;
				if (grid[y][x + 1] == 'X')
				{
					Left = false;
					tempX++;
				}
				else
				{
					Left = true;
					tempX--;
				}

				while (!Fini)
				{
					if (Left)
					{
						while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];

							if (BaseLevel[tempY - 1][tempX] == 'D' || BaseLevel[tempY - 1][tempX] == 'L' || BaseLevel[tempY - 1][tempX] == 'D')
							{
								grid[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
								colors[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
							}
							else if (BaseLevel[tempY + 1][tempX] == 'D' || BaseLevel[tempY + 1][tempX] == 'L' || BaseLevel[tempY + 1][tempX] == 'D')
							{
								grid[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
								colors[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
							}

							if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
							{
								break;
							}
							tempX--;
						}
						tempX = x - 1;
						tempY = y - 1;
						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempX--;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY - 1][tempX] == 'D' || BaseLevel[tempY - 1][tempX] == 'L' || BaseLevel[tempY - 1][tempX] == 'D')
								{
									grid[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
									colors[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX ];
								}
								else if (BaseLevel[tempY][tempX + 1] == 'D' || BaseLevel[tempY + 1][tempX] == 'L' || BaseLevel[tempY + 1][tempX] == 'D')
								{
									grid[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
									colors[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempX--;
							}
							tempX = x - 1;
							tempY -= 1;
						}
						tempX = x - 1;
						tempY = y + 1;

						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempX--;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY - 1][tempX] == 'D' || BaseLevel[tempY - 1][tempX] == 'L' || BaseLevel[tempY - 1][tempX] == 'D')
								{
									grid[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
									colors[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
								}
								else if (BaseLevel[tempY + 1][tempX] == 'D' || BaseLevel[tempY + 1][tempX] == 'L' || BaseLevel[tempY + 1][tempX] == 'D')
								{
									grid[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
									colors[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempX--;
							}
							tempX = x - 1;
							tempY += 1;
						}
					}
					else
					{
						while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];

							if (BaseLevel[tempY - 1][tempX] == 'D' || BaseLevel[tempY - 1][tempX] == 'L' || BaseLevel[tempY - 1][tempX] == 'D')
							{
								grid[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
								colors[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
							}
							else if (BaseLevel[tempY + 1][tempX] == 'D' || BaseLevel[tempY + 1][tempX] == 'L' || BaseLevel[tempY + 1][tempX] == 'D')
							{
								grid[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
								colors[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
							}

							if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
							{
								break;
							}
							tempX++;
						}
						tempX = x + 1;
						tempY = y - 1;
						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempX++;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY - 1][tempX] == 'D' || BaseLevel[tempY - 1][tempX] == 'L' || BaseLevel[tempY - 1][tempX] == 'D')
								{
									grid[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
									colors[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
								}
								else if (BaseLevel[tempY + 1][tempX] == 'D' || BaseLevel[tempY + 1][tempX] == 'L' || BaseLevel[tempY + 1][tempX] == 'D')
								{
									grid[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
									colors[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempX++;
							}
							tempX = x + 1;
							tempY -= 1;
						}
						tempX = x + 1;
						tempY = y + 1;

						while (BaseLevel[tempY][tempX] != 'X' && grid[tempY][tempX] == 'X')
						{
							grid[tempY][tempX] = BaseLevel[tempY][tempX];
							colors[tempY][tempX] = BaseLevel[tempY][tempX];
							tempX++;
							while (BaseLevel[tempY][tempX] != 'X'&& grid[tempY][tempX] == 'X')
							{
								grid[tempY][tempX] = BaseLevel[tempY][tempX];
								colors[tempY][tempX] = BaseLevel[tempY][tempX];

								if (BaseLevel[tempY - 1][tempX] == 'D' || BaseLevel[tempY - 1][tempX] == 'L' || BaseLevel[tempY - 1][tempX] == 'D')
								{
									grid[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
									colors[tempY - 1][tempX] = BaseLevel[tempY - 1][tempX];
								}
								else if (BaseLevel[tempY + 1][tempX] == 'D' || BaseLevel[tempY + 1][tempX] == 'L' || BaseLevel[tempY + 1][tempX] == 'D')
								{
									grid[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
									colors[tempY + 1][tempX] = BaseLevel[tempY + 1][tempX];
								}

								if (BaseLevel[tempY][tempX] == 'D' || BaseLevel[tempY][tempX] == 'd' || BaseLevel[tempY][tempX] == 'L')
								{
									break;
								}
								tempX++;
							}
							tempX = x + 1;
							tempY += 1;
						}
					}
					Fini = true;
				}
			}
			else if (grid[y][x] == KNIGHT)
			{
				grid[y][x] = CORPSE;
				colors[y][x] = CORPSE;
			}
			else if (grid[y][x] == CORPSE && grid[12][7] == TRONE)
			{
				carryCorpse = true;
				grid[y][x] = ' ';
				colors[y][x] = ' ';
			}
			else if (grid[y][x] == CHESTCLOSE)
			{
				key = true;
				grid[y][x] = 'c';
				colors[y][x] = 'c';
			}
			else if (grid[y][x] == DOORLOCKED && key)
			{
				grid[y][x] = ' ';
				colors[y][x] = ' ';
			}
			else if (grid[y][x] == PLATE && carryChair)
			{
				carryChair = false;
				grid[y][x] = TRONE;
				colors[y][x] = TRONE;
			}
			else if (grid[y][x] == TRONE && carryCorpse)
			{
				carryCorpse = false;
				grid[y][x] = FULLTRONE;
				colors[y][x] = FULLTRONE;
			}
			else if (grid[y][x] == LEVEROFF)
			{
				if (grid[12][7] == FULLTRONE)
				{
					grid[y][x] == LEVERON;
					grid[3][27] = DOORLEFTRIGHT;
					colors[3][27] = DOORLEFTRIGHT;
				}
				else
				{
					win = 2;
					quit = true;
				}
			}
			else if (grid[y][x] == TELEPORTER)
			{
				win = 1;
				quit = true;
			}
			else if (grid[y][x] == CHAIR)
			{
				carryChair = true;
				grid[y][x] = ' ';
				colors[y][x] = ' ';
			}
		}

	} while (!quit);

	if (win == 1)
		std::cout << "You are teleported to your home. You won!!!" << std::endl;
	else if (win == 2)
	{
		std::cout << "You did not place someone on the throne before leaving! A trap open under you and you fall to your death" << std::endl;
	}
	else
	{
		std::cout << "QUIT!" << std::endl;
	}

}
