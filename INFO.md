This is a prototype of an Game Engine with Raycasting.
It has a functional internal division into states and scenes; former being a way to divide mechanically different parts of the program,
later being a way to divide Menus with Buttons and Text in a particulat state.
On the visual side the Engine has support of Buttons, Images and Text in Scenes; also in GamePlay GameState
it supports raycasted walls with independent cube texture mapped walls from level data, affine mapped independent ceiling and floor and
also includes an editor in Orthogonal projection to edit the included map. It also correctly displays sprites with rotation information. It has divided particular sections of the global program into Managers, such as Resource Manager and LogManager which handles error and log info output to files.


On starting the included executable we are greeted by a Main Menu. It has the option of hopping inside the GameEngine to stroll about on the map, interacting with doors and testing features.
We can also pause the Game at any time with The Escape Button which takes us to the Pause State from which we can resume or exit to Main Menu/Desktop.

In the Main Menu we can also see the usage of scenes with Buttons that take us to the Help Scene which details the controls.
Ingame:
W - Forward ::: S- Backwards 
A - Left ::: D - Right 
Q - Rotate Left ::: E - Rotate Right 
Mouse - Rotation Left-Right
Left Mouse Button - Open Door/Activate
Shift - Sprint
Editor:   
WSAD - to change Cursor position
QE - to change Camera Rotation
RF - to change Camera Tilt
ZX - to change Camera Zoom
1-9 - PICK Wall Texture (also 0 which is reserved for doors)
SPACE - to place walls

In the Editor which we can get to by clicking the "Editor" Button in Main Menu;
we can change the level design by placing walls and doors to our liking, saving by exiting with Escape Key.