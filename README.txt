# Pacman
 by Omri Shahar Revivo - 315873471  & Gal Aviezri - 208782912
 
 This is Our version of Pacman, besides the basic features we added: ascii art at welcome screen, PC alarm when collision with ghosts, some nice colors, 
3 modes : 
 1) easy - ghosts move randomly
 2) medium - ghosts chase pacman and once in every 15 moves they will do 5 random moves
 3) expert - ghosts chase pacman all theway 
 
 a fruit which appears randomly in a random spot once in a while and will grant bonus points
 
 an option on menu to load a specific level from working directory
 
 ***any map that follows the game format can be loaded and be played***
 
format: 
create a file of type ".screen" and use each of the following character:
'@' -  pacman default position (only the first is addressed)
'$' - a ghost default position (can be many)
' ' - (a space) where food will be printed
'%' - a tile to be left blank
'&' - a space for the legend (score + lives) [the legend spans 3 rows with 20 characters each and is treated as wall block by creatures in the game.] 

EXTRAS: 

#1 if given cmdline arg "-save" the game will record and save the last game played (sequence of levels). 
   incase a game was quit in the middle by pressing TAB the level won't be save.

#2 if given cmdline arg "-load" the game will play a recorded game (if any) and will output it to the screen,
   going between all levels that have a recording.
   at the end of each round a test result will output.

#2.1  if given "-load -silent" the above will occur without printing the game progression, i.e. only printing test results.

#3 The format of .steps files is ADWWW+5D - first movement direction(A) is for pacman; assuming there are 4 ghosts: DWWW is the movement directions 
for the ghosts by order;  +5D - the +/- signals if a fruit is visible(+) or not , the number is the avatar of the fruit and the letter at the end is the movement direction

#4 the format of .results files is  259C(x,y); the number represents the iteration in which the event occured. the letter represents the kind of event (Collision,Lose,Win)
   and the point is the fruit's randomly selected new position.
