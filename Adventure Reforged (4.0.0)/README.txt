Version-
1.0
Made for GB Studio 4.0.0
Released -/-/----

Description-
Adventure Reforged is an engine plugin that completely replaces the Adventure scene type. It includes the following features:
-More performant player movement
-Smoother diagonal player movement
-Solid actors that the player cannot move through
-Actors pass through each other and the player
-Toggleable background collision
-Toggleable swimming movement

Installation instructions-
Create a folder called 'plugins' inside the root folder of your GB Studio project.
Add the 'Adventure Reforged' folder that contains this readme file to the 'plugins' folder.
Compile your game.

Useage instructions-
-Player movement changes will be applied automatically after installing the plugin. Please note that any changes to the player's speed will not be reflected in Adventure scenes, as movement speeds are now hardcoded into the scene type.
-Solid actors can be created by setting the collision type of an actor to None. The player will be unable to move through them. Solid actors moving into the player is not supported.
-To use toggleable background collision, draw ladder tiles on top of solid collision tiles. The Engine Field Update event can then be used to update the Toggleable Collision field and toggle those tiles on and off. Actors will never move through toggleable collision whether it is on or off.
-To use swimming movement, the Engine Field Update event can be used to update the Swimming engine field and toggle it on and off.
-The Actors Pass Through Actors plugin behaviour is included in this plugin, so don't include it in Adventure Reforged projects in case of conflicts.

Credits-
Made by Shin
https://gbstudiolab.neocities.org/
Attribution to Shin or https://gbstudiolab.neocities.org/ in credits is appreciated, but not necessary.