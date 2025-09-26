Version-
1.3
Made for GB Studio 4.1.2
Released 18/9/2025, updated 25/9/2025

Description-
Talking Actors and Dialogue Prompt Actors is an engine plugin that changes an actor's animation while dialogue is being drawn, useful for animating talking characters during cutscenes. It also allows an additional actor to be used as a prompt when a button can be pressed to advance dialogue.

Installation instructions-
Create a folder called 'plugins' inside the root folder of your GB Studio project.
Add the 'Talking Actors and Dialogue Prompt Actors' folder that contains this readme file to the 'plugins' folder.
Compile your game.

Talking Actors usage instructions-
-To set up a sprite for use with the plugin, set its Animation Type to Fixed Direction + Movement. The Idle animation will be used when dialogue is not being drawn, and the Moving animation will be used when dialogue is being drawn. You can also use animation states as normal with this plugin.
-Add one or more actors with compatible sprites to your scene. Existing actor features like animation speed and hiding actors should be compatible with this plugin.
-Add an Engine Field Update event to your scene. In the event's drop down menu, you should see the new option Set Talking Actor in the Dialogue category. Use this option to set which actor will be animated while dialogue is being drawn. Actors are referred to by their index (actor 1, actor 2, etc) which you can see in the editor by leaving an actor's name empty. You can also change an actor's index by removing it and readding it to the scene, which will place it at the end of the list.
-You can add multiple Engine Field Update events between other events in your scene to change which actor is being animated, or disable all animation.

Dialogue Prompt Actors usage instructions-
-To set up a sprite for use with the plugin, set its Animation Type to Fixed Direction + Movement. The Moving animation will be used when a button can be pressed to advance dialogue, and the Idle animation at all other times. You can also use animation states as normal with this plugin.
-Add an Engine Field Update event to your scene. In the event's drop down menu, you should see the new option Set Dialogue Prompt Actor in the Dialogue category. Use this option to set which actor will be used as a dialogue prompt. Actors are referred to by their index (actor 1, actor 2, etc) which you can see in the editor by leaving an actor's name empty. You can also change an actor's index by removing it and readding it to the scene, which will place it at the end of the list.
-If you want the dialogue prompt to display over the top of dialogue boxes and the overlay, add a GBVM Script event with the following two lines to your scene's On Init script.
VM_SET_CONST_UINT8 _show_actors_on_overlay, 1
VM_SET_CONST_UINT8 _overlay_priority, 0


Credits-
Made by Shin
https://gbstudiolab.neocities.org/
Attribution to Shin or https://gbstudiolab.neocities.org/ in credits is appreciated, but not necessary.