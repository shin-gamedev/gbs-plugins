Version-
1.0
Made for GB Studio 4.1.2
Released 18/9/2025

Description-
Talking Actors is an engine plugin that changes an actor's animation while dialogue is being drawn, useful for animating talking characters during cutscenes.

Installation instructions-
Create a folder called 'plugins' inside the root folder of your GB Studio project.
Add the 'Talking Actors' folder that contains this readme file to the 'plugins' folder.
Compile your game.

Useage instructions-
-To set up a sprite for use with the plugin, set its Animation Type to Fixed Direction + Movement. The Idle animation will be used when dialogue is not being drawn, and the Moving animation will be used when dialogue is being drawn. You can also use animation states as normal with this plugin.
-Add one or more actors with compatible sprites to your scene. Existing actor features like animation speed and hiding actors should be compatible with this plugin.
-Add an Engine Field Update event to your scene. In the event's drop down menu, you should see the new option Set Talking Actor in the Dialogue category. Use this option to set which actor will be animated while dialogue is being drawn. Actors are referred to by their index (actor 1, actor 2, etc) which you can see in the editor by leaving an actor's name empty. You can also change an actor's index by removing it and readding it to the scene, which will place it at the end of the list.
-You can add multiple Engine Field Update events between other events in your scene to change which actor is being animated, or disable all animation.

Credits-
Made by Shin
https://gbstudiolab.neocities.org/
Attribution to Shin or https://gbstudiolab.neocities.org/ in credits is appreciated, but not necessary.