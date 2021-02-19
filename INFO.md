# Catacombs of Styr - User Manual


## Introduction
###Description
This is a prototype of an Game Engine with Raycasting.

### Functionality
It has a functional internal division into states and scenes; former being a way to divide mechanically different parts of the program,
later being a way to divide Menus with Buttons and Text in a particular state.
On the visual side the Engine has support of Buttons, Images and Text in Scenes; also in GamePlay GameState
it supports raycasted walls with independent cube texture mapped walls from level data, affine mapped independent ceiling and floor and
also includes an editor in Orthogonal projection to edit the included map. It also correctly displays sprites with rotation information. It has divided particular sections of the global program into Managers, such as Resource Manager and Log Manager which handles error and log info output to files.

## Walk through the Features
#####On starting the included executable we are greeted by a Main Menu.

<img src="imMainMenu.png" alt="Main Menu" width="100%"/>

##### Using the first provided button "Enter Catacombs" we now have the option of hopping inside the GameEngine to stroll about on the map, interacting with doors and testing features.


<img src="imGameInside.png" alt="Game First Look" width="100%"/>

##### Upon clicking that we are greeted by the inside of the Game World with the level data loaded from one of the provided maps.\n We can observe the walls that are raycasted column by column and affine mapped floor and ceiling. \n Here we have the option of traversing the ingame level using the controls below.

Controls  | Type | Key Binding
:---------| :--- | :-----------:
Movement  | Forward | W
^  | Backwards | S 
^  | Left | A
^  | Right | D
^  | Rotation | Mouse Tracking
^  | Rotation Left Alt.| Q
^  | Rotation Right Alt. | E
^  | Sprint | Shift
Interaction  | Open Door | RMB
Meta  | Pause Menu | Escape
Debug  | Increase Health | G
^  | Decrease Health | B


*RMB-Right_Mouse_Button

##### They are also available using the main menu button "Help".
<img src="imMainHelp.png" alt="Main Menu Help" width="50%"/>

#####We can now walk around observing the Test Level.

<img src="imGameWalls.png" alt="GameWalls" width="100%"/>
#####Raycasted walls with texture mapping and affine mapped ceiling and floor.

<img src="gifRotation.gif" alt="gifRotation.gif" width="50%"/>
#####Relative Rotation Sprite Drawing
<img src="gifDoor.gif" alt="gifDoor.gif" width="50%"/>
#####Doors
<img src="gifHealth.gif" alt="Main Menu" width="20%"/>
#####Health Dependent Portrait
<img src="imGameBlur.png" alt="imGameBlur.png" width="50%"/>
#####By pressing the Escape Key we can pull up Pause Menu which stops interaction with the gameworld and return to the Main Menu.
<img src="imMainEditor.png" alt="imGameEditor.png" width="50%"/>
#####We can now hop in to the Editor

#####The controls below detail the available options.

Controls  | Type | Key Binding
:---------| :--- | :-----------:
Camera Movement  | Translation | W,S,A,D
^  | Rotation | Q,E
^  | Zoom | Z,X
^  | Tilt | R,F
Tools  | Place/Remove | Space
^  | Pick Wall to place| 1-9 
^  | Pick Door  to place| 0
Meta  | Exit to Main Menu | Escape

<img src="gifETranslation.gif" alt="gifETranslation.gif" width="100%"/>
#####Translation
<img src="gifEZoom.gif" alt="gifEZoom.gif" width="100%"/>
#####Zoom
<img src="gifERotation.gif" alt="gifERotation.gif" width="100%"/>
#####Rotation
<img src="gifETilt.gif" alt="gifETilt.gif" width="100%"/>
#####Tilt
<img src="gifEPlace.gif" alt="gifEPlace.gif" width="100%"/>
#####Placing Walls/Door


####And here ends the tour. Good Luck!





