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
'&' - a space for the legend (score + lives) [the legend spans 3 rows with 20 characters each]

