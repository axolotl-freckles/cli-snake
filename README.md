# cli-snake
A windows (for now, I hope) comand promp snake game

## Use

Just type the executable name in the terminal and that should launch the main menu.

The ESC key exits the current screen or closes the game (if on the main menu).

To navigate the menu follow the promt on top, the navigation keys change according
to your current game key configuration, so make shure to choose them carefully.
An arrow will appear pointing to your current selection. To select press ENTER.

First thing you may want to check are the key bindings. They are under the
"Keyboard settings" option. There it will show wich keys are currently used and for
what direction. The arrow will point to the key you might change. To change a key,
press ENTER when the arrow points to that option. The key will change to an
underscore and the first key you press next will be the new key. Keep in mind that
this dumb behaviour might cause problems if you select a special key. Press EXIT
or go to the exit option to return to the main menu.

In "Game Settings" you will find the option to change the game screen or the game
border. The game screen defines the space that the snake can move in and the game
border will determine if the snake dies when it hits the wall (solid) or if it 
teleports to the other side (borderless).

## Game

Use your current selected keys to move the snake. Your goal is to grab the apple
that appears in the screen while avoiding colliding with yourself. Everytime you
eat an apple, your length will increase.

Depending on wich border type you selected, the border will appear lined with
'#' or '+'. If you see '#' that means that the game will end if you collide with
it, if instead, you see '+', that means that you will teleport to the other side
when you cross the border.

You may press ESC anytime while playing to exit (will add a pause menu if possible).

## Code

This was mainly a thing of _"did it because it could be done without thinking if it
should be done"_ so it may be full of things that could be done better.

This little experiment was made to understand and to apply knoledge about threads, some
rudimentary render-simulation pipelines and static libraries. So feel free to see what makes things tick.
It was also an excuse to dip my toes into a more developer oriented approach, considering
readability and structure while developing. It's not perfect, but it's a start.
